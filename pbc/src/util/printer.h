/*
 * @Author: modnarshen
 * @Date: 2022/08/05 18:20:08
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <cstdarg>
#include <iostream>
#include <sstream>

namespace pbc {
extern bool DEBUG_MODE;
constexpr std::size_t MAX_BUFFER_SIZE = 1024;
extern char buffer[MAX_BUFFER_SIZE];

class Printer {
public:
    static void raw_print(std::ostream &os, const char *fmt, std::va_list arg_list);
    static void raw_print(std::ostringstream &oss, const char *fmt, std::va_list arg_list);
};
} // namespace pbc

// macro-like functions
void OUTPUT_DEBUG(const char *fmt, ...);
void OUTPUT_INFO(const char *fmt, ...);
void OUTPUT_ERROR(const char *fmt, ...);
void OUTPUT_STDOUT(const char *fmt, ...);
void OUTPUT(std::ostringstream &oss, const char *fmt, ...);
