/*
 * @Author: modnarshen
 * @Date: 2022/05/17 16:12:45
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <string>
#include <vector>

#include "macro.h"

namespace pbc {

inline std::string &trim(std::string &s) {
    COND_RET(s.empty(), s);
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" \r") + 1);
    return s;
}

inline std::size_t count(const std::string &s, char c) {
    return std::count(s.begin(), s.end(), c);
}

// 以delims集合中的字符作为分隔符
inline void split(const std::string &src, const std::string &delims, std::vector<std::string> &ret) {
    // split最优雅的实现
    std::string::size_type begin_pos = src.find_first_not_of(delims, 0);
    std::string::size_type end_pos = src.find_first_of(delims, begin_pos);
    while (std::string::npos != begin_pos || std::string::npos != end_pos) {
        ret.emplace_back(src.substr(begin_pos, end_pos - begin_pos));
        begin_pos = src.find_first_not_of(delims, end_pos);
        end_pos = src.find_first_of(delims, begin_pos);
    }
}

} // namespace pbc