/*
 * @Author: modnarshen
 * @Date: 2022/05/17 16:12:45
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <string>
#include <vector>

namespace pbc {

// 以delims集合中的字符作为分隔符
inline void split(const std::string &src, const std::string &delims, std::vector<std::string> &ret) {
    // split最优雅的实现
    std::string::size_type begin_pos = src.find_first_not_of(delims, 0);
    std::string::size_type end_pos = src.find_first_of(delims, begin_pos);
    while (std::string::npos != begin_pos || std::string::npos != end_pos) {
        ret.emplace_back(src.substr(begin_pos, end_pos - begin_pos));
        begin_pos = src.find_first_not_of(delims, begin_pos);
        end_pos = src.find_first_of(delims, begin_pos);
    }
}

} // namespace pbc