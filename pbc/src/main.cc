/*
 * @version: UAMobile 2022.0715
 * @Author: modnarshen
 * @Date: 2022/04/27 11:28:50
 * @LastEditors: modnarshen
 * @Description:
 */
#include <iomanip>
#include <iostream>
#include <memory>
#include <cstdlib>

#include "pbc.h"
#include "pbc_info.h"
#include "pbc_printer.h"
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
    pbc::PbConst::GetInst().Init(argv[1]);
    return 0;
}
