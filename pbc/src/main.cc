/*
 * @version: UAMobile 2022.0715
 * @Author: modnarshen
 * @Date: 2022/04/27 11:28:50
 * @LastEditors: modnarshen
 * @Description: 工具程序执行入口
 */
#include <getopt.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>

#include "pb_const.h"
#include "pbc_info.h"
#include "util/macro.h"
#include "util/printer.h"
#include "util/timer.h"

static const char *short_opts = "I:o:n:hdv";
static const struct option long_opts[] = {{"proto_path", required_argument, nullptr, 'I'},
                                          {"cpp_out", required_argument, nullptr, 'o'},
                                          {"file_name", no_argument, nullptr, 'n'},
                                          {"help", no_argument, nullptr, 'h'},
                                          {"debug", no_argument, nullptr, 'd'},
                                          {"version", no_argument, nullptr, 'v'},
                                          {nullptr, no_argument, nullptr, 0}};

void version() {
    OUTPUT_STDOUT("version: %u.%u", pbc_VERSION_MAJOR, pbc_VERSION_MINOR);
}

void usage(char *argv[]) {
    OUTPUT_STDOUT("Usage: %s [OPTION] PROTO_FILES", argv[0]);
    OUTPUT_STDOUT("根据给定的选项对 PROTO_FILES 进行解析并输出相应内容:");
    OUTPUT_STDOUT("  -IPATH, --proto_path=PATH  指定查询的 .proto 文件目录，如果 import 了文件，也要填充进来");
    OUTPUT_STDOUT("  -o, --cpp_out              指定生成的 .pbc.h, .pbc.cc 文件输出目录");
    OUTPUT_STDOUT("  -n, --file_name            按照给定的 file_name 来重新命名生成的 .pbc.h, .pbc.cc 文件名");
    OUTPUT_STDOUT("  -d, --debug                以 DEBUG 模式运行此程序，可获取更多程序运行信息");
    OUTPUT_STDOUT("  -v, --version              获取版本信息并退出");
    OUTPUT_STDOUT("  -h, --help                 获取此帮助信息并退出");
}

int main(int argc, char *argv[]) {
    std::string proto_filepath;
    std::vector<std::string> proto_file_path;
    std::string out_file_path;
    std::string out_file_name;

    int opt = 0;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
            case 'h': {
                usage(argv);
                return 0;
            }
            case 'I': {
                proto_file_path.emplace_back(optarg);
                break;
            }
            case 'o': {
                out_file_path.assign(optarg);
                break;
            }
            case 'n': {
                out_file_name.assign(optarg);
                break;
            }
            case 'd': {
                pbc::DEBUG_MODE = true;
                break;
            }
            case 'v': {
                version();
                return 0;
            }
            default:
                usage(argv);
                return 2;
        }
    }

    if (argc == optind) {
        usage(argv);
        return 3;
    }
    proto_filepath.assign(argv[optind]);
    if (proto_filepath.empty() || proto_file_path.empty() || out_file_path.empty()) {
        usage(argv);
        return 4;
    }

    int ret = pbc::PbConst::GetInst().Init(proto_filepath, proto_file_path, out_file_path, out_file_name);
    COND_RET_ELOG(ret != 0, ret, "pbc init failed|file:%s|ret:%d", proto_filepath.c_str(), ret);

    ret = pbc::PbConst::GetInst().Parse();
    COND_RET_ELOG(ret != 0, ret, "pbc parse failed|file:%s|ret:%d", proto_filepath.c_str(), ret);

    return 0;
}
