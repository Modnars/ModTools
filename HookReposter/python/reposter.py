#!/usr/bin/env python3.6
# -*- coding: UTF-8 -*-

import os, copy
import json, re, datetime, logging, logging.handlers
import requests, flask


APP_NAME = "HookReposter"
RE_PATT_SINGLE_FIELD = re.compile(r'\${(.*?)}')
RE_PATT_REPEAT_FIELD = re.compile(r'\$\[(.*?)\]', re.DOTALL)


def isList(data) -> bool:
    return type(data).__name__ == 'list'


def isDict(data) -> bool:
    return type(data).__name__ == 'dict'


def isStr(data) -> bool:
    return type(data).__name__ == 'str'


# 服务进程
app = flask.Flask(APP_NAME)

# 日志相关
LOG_FORMAT = "%(threadName)s|%(asctime)s|%(filename)s:%(lineno)d|%(levelname)s|%(funcName)s|%(message)s"
LOG_PATH   = "logs"

def setupLogHandler():
    if not os.path.exists(LOG_PATH):
        os.makedirs(LOG_PATH)

    # app.debug = True

    formatter = logging.Formatter(LOG_FORMAT)

    # 添加输出到debug的handler
    log_path = LOG_PATH + "/reposter.log"
    log_handler = logging.handlers.TimedRotatingFileHandler(log_path, when="MIDNIGHT", interval=1, backupCount=30)
    log_handler.suffix = "%Y%m%d.log"
    log_handler.setFormatter(formatter)
    log_handler.setLevel(logging.DEBUG)
    app.logger.addHandler(log_handler)

setupLogHandler()


def loadJsonObject(file_path: str) -> dict:
    ret = None
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            ret = json.loads(''.join(line[:-1] for line in f))
    except Exception:
        ret = None
        app.logger.error("load json file failed|file:%s", file_path)
    return ret


# 配置相关
class RepostConfWrapper(object):
    def __init__(self, config_file: str) -> None:
        super().__init__()
        self._all_conf = loadJsonObject(config_file)

        if self._all_conf is None:
            app.logger.error("init repost conf failed")
            self._is_ready = False
        else:
            self._is_ready = self.__checkConf()


    def isReady(self) -> bool:
        return self._is_ready


    def getParseRule(self, source: str) -> dict:
        if source in self._all_conf and "parse" in self._all_conf[source]:
            return self._all_conf[source]["parse"]
        return dict()


    def getRepostHosts(self, source: str) -> list:
        if source in self._all_conf and "hosts" in self._all_conf[source]:
            return self._all_conf[source]["hosts"]
        return list()


    def getRawRepostData(self, source: str, idx: int) -> dict:
        ret = dict()
        if source not in self._all_conf: return ret
        if "hosts" not in self._all_conf[source]: return ret
        if idx >= len(self._all_conf[source]["hosts"]): return ret
        if "data" not in self._all_conf[source]["hosts"][idx]: return ret
        return copy.deepcopy(self._all_conf[source]["hosts"][idx]["data"])


    def __checkConf(self) -> bool:
        # TODO modnarshen 完善配置检查逻辑
        return True

repostConfWrapper = RepostConfWrapper("repost_rules.json")
if not repostConfWrapper.isReady():
    app.logger.error('init repost conf failed')
    exit(1)


def doGetJsonField(json_data: dict, field_path: str):
    ret = list()
    cur = json_data
    path = field_path

    pos = path.find('.')
    while pos != -1:
        cur = cur[path[:pos]]
        if isList(cur):
            for d in cur:
                ret += [doGetJsonField(d, path[pos+1:])]
            return ret
        path = path[pos+1:]
        pos = path.find('.')
    return cur[path]


def GetJsonField(json_data: dict, field_path: str):
    ret = None
    try:
        ret = doGetJsonField(json_data, field_path)
    except Exception as e:
        app.logger.error("Catch Exception:", e)
        ret = None
    return ret


def parseLine(src: str, parse_content: dict) -> str:
    beg = '${' 
    end = '}'
    len_beg = len(beg)
    len_end = len(end)
    all = re.findall(RE_PATT_REPEAT_FIELD, src)
    for s in all:
        beg_pos = s.find(beg)
        end_pos = -1
        prompt = []
        parse = []
        while beg_pos != -1:
            prompt.append(s[end_pos+1:beg_pos])
            end_pos = s.find(end, beg_pos+len_beg)
            key = s[beg_pos+len_beg:end_pos]
            parse.append(parse_content[key] if key in parse_content else '')
            beg_pos = s.find(beg, end_pos+len_end)
        sub = ''
        for t in zip(*parse):
            for i in range(len(t)):
                sub += prompt[i] + str(t[i])
        src = src.replace('$[%s]' % s, sub)

    all = re.findall(RE_PATT_SINGLE_FIELD, src)
    for s in all:
        src = src.replace('${%s}' % s, parse_content[s] if s in parse_content else '')
    return src


def makeRespData(data: dict, parse_content: dict) -> None:
    for k in data:
        if isDict(data[k]):
            makeRespData(data[k], parse_content)
        elif isList(data[k]):
            for i in range(len(data[k])):
                if isDict(data[k][i]):
                    makeRespData(data[k][i], parse_content)
                elif isStr(data[k][i]):
                    data[k][i] = parseLine(data[k][i], parse_content)
        elif isStr(data[k]):
            data[k] = parseLine(data[k], parse_content)


def doHttpRequest(url: str, method: str, data: dict):
    if method == 'GET':
        return None
    return requests.post(url, data=json.dumps(data, ensure_ascii=False).encode('utf-8')).json()


'''
处理POST请求
'''
@app.route('/', methods=['POST'])
def process():
    rsp = dict()
    ret = 200
    try:
        source = flask.request.args.get('source')
        if source is None: raise RuntimeError('no url param `source`')

        recv_data = flask.request.get_json()

        parse_rule = repostConfWrapper.getParseRule(source)
        parse_content = dict()
        for k in parse_rule:
            parse_content[k] = GetJsonField(recv_data, parse_rule[k])
        app.logger.info("parse content:%s", str(parse_content))

        for host in repostConfWrapper.getRepostHosts(source):
            data = copy.deepcopy(host["data"])
            makeRespData(data, parse_content)

            app.logger.info(doHttpRequest(host["url"], host["method"], data))

        rsp["message"] = "ok"
        ret = 200
    except Exception as e:
        app.logger.warn("catch exception|details: %s", str(e))
        rsp["message"] = "process failed"
        ret = 500

    rsp["time"] = str(datetime.datetime.now())
    app.logger.debug("response:%s|ret:%d", str(rsp), ret)
    return flask.make_response(flask.jsonify(rsp), ret)


def main():
    deploy_conf = loadJsonObject("config.json")
    if "deploy_host" not in deploy_conf or "deploy_port" not in deploy_conf:
        app.logger.error("load deploy config failed")
        exit(1)
    app.run(host=deploy_conf["deploy_host"], port=deploy_conf["deploy_port"])


if __name__ == "__main__":
    main()
