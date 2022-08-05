/*
 * @version: UAMobile 2022.0715
 * @Author: modnarshen
 * @Date: 2022/04/27 11:28:50
 * @LastEditors: modnarshen
 * @Description: 工具程序执行入口
 */
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>

#include "pb_const.h"
#include "pbc_info.h"
#include "util/macro.h"
#include "util/printer.h"
#include "util/timer.h"

void version() {
    OUTPUT_STDOUT("version: %u.%u", pbc_VERSION_MAJOR, pbc_VERSION_MINOR);
}

void usage(int argc, char *argv[]) {
    OUTPUT_STDOUT("usage: %s file_path", basename(argv[0]));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        version();
        usage(argc, argv);
        return EXIT_FAILURE;
    }
    std::string proto_file = argv[1];
    int ret = pbc::PbConst::GetInst().Init(proto_file);
    COND_RET_ELOG(ret != 0, ret, "pbc init failed|file:%s", proto_file.c_str());

    ret = pbc::PbConst::GetInst().Parse();
    COND_RET_ELOG(ret != 0, ret, "pbc parse failed|file:%s", proto_file.c_str());

    return 0;
}
