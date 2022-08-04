/*
 * @Author: modnarshen
 * @Date: 2022/05/10 19:17:56
 * @LastEditors: modnarshen
 * @Description:
 */
#include <cstdio>

#include "pbc_printer.h"

namespace pbc {
bool DEBUG_MODE              = false;
char buffer[MAX_BUFFER_SIZE] = {0};

void PbcPrinter::raw_print(std::ostream &os, const char *fmt, std::va_list arg_list) {
    std::vsnprintf(buffer, sizeof(buffer), fmt, arg_list);
    os << buffer << std::endl;
}

void PbcPrinter::raw_print(std::ostringstream &oss, const char *fmt, std::va_list arg_list) {
    std::vsnprintf(buffer, sizeof(buffer), fmt, arg_list);
    oss << buffer;
}
} // namespace pbc

// 运行时日志
void OUTPUT_DEBUG(const char *fmt, ...) {
    if (pbc::DEBUG_MODE) {
        std::va_list arg_list;
        va_start(arg_list, fmt);
        pbc::PbcPrinter::raw_print(std::cout, fmt, arg_list);
        va_end(arg_list);
    }
}

void OUTPUT_INFO(const char *fmt, ...) {
    std::va_list arg_list;
    va_start(arg_list, fmt);
    pbc::PbcPrinter::raw_print(std::cout, fmt, arg_list);
    va_end(arg_list);
}

void OUTPUT_ERROR(const char *fmt, ...) {
    std::va_list arg_list;
    va_start(arg_list, fmt);
    pbc::PbcPrinter::raw_print(std::cerr, fmt, arg_list);
    va_end(arg_list);
}

// 标准输出
void OUTPUT_STDOUT(const char *fmt, ...) {
    std::va_list arg_list;
    va_start(arg_list, fmt);
    pbc::PbcPrinter::raw_print(std::cout, fmt, arg_list);
    va_end(arg_list);
}

void OUTPUT(std::ostringstream &oss, const char *fmt, ...) {
    std::va_list arg_list;
    va_start(arg_list, fmt);
    pbc::PbcPrinter::raw_print(oss, fmt, arg_list);
    va_end(arg_list);
}
