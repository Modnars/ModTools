#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

'''
Description:
version: 1.0.0
Author: modnarshen
Date: 2021/04/01 20:04:43
LastEditors: modnarshen
LastEditTime: 2021/06/30 19:53:44
'''

import logging
import logging.handlers
import time
import os
import sys

import config

LOG_FORMAT = "%(threadName)s|%(asctime)s|%(filename)s:%(lineno)d|%(levelname)s|%(funcName)s|%(message)s"

# 模块名
name = config.PROJ_NAME
# 日志路径
LOG_PATH = "logs"


def setupLogger():
    if not os.path.exists(LOG_PATH):
        os.makedirs(LOG_PATH)

    logger = logging.getLogger(name)
    logger.setLevel(logging.DEBUG)
    formatter = logging.Formatter(LOG_FORMAT)

    if config.DEBUG_MODE is True:
        # 添加到标准输出的handler
        console_handler = logging.StreamHandler(sys.stdout)
        console_handler.setFormatter(formatter)
        logger.addHandler(console_handler)

    # 添加输出到debug的handler
    debug_path = LOG_PATH + "/debug.log"
    debug_handler = logging.handlers.TimedRotatingFileHandler(debug_path, when="MIDNIGHT", interval=1, backupCount=30)
    debug_handler.suffix = "%Y%m%d.log"
    debug_handler.setFormatter(formatter)
    debug_handler.setLevel(logging.DEBUG)
    logger.addHandler(debug_handler)

    # 添加输出到warn的handler
    warn_path = LOG_PATH + "/warn.log"
    warn_handler = logging.handlers.TimedRotatingFileHandler(warn_path, when="MIDNIGHT", interval=1, backupCount=30)
    warn_handler.suffix = "%Y%m%d.log"
    warn_handler.setFormatter(formatter)
    warn_handler.setLevel(logging.WARN)
    logger.addHandler(warn_handler)

    # 添加输出到error的handler
    error_path = LOG_PATH + "/error.log"
    error_handler = logging.handlers.TimedRotatingFileHandler(error_path, when="MIDNIGHT", interval=1, backupCount=30)
    error_handler.suffix = "%Y%m%d.log"
    error_handler.setFormatter(formatter)
    error_handler.setLevel(logging.ERROR)
    logger.addHandler(error_handler)

    return logger


Logger = setupLogger()
