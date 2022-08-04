/*
 * @Author: modnarshen
 * @Date: 2022/05/18 17:41:09
 * @LastEditors: modnarshen
 * @Description:
 */
#include "pbc.h"
#include "util/macro.h"

namespace pbc {
bool PbConst::Init(const std::string &src_file_path, const std::string &out_file_name) {
    auto pos = src_file_path.find_last_of('/');
    if (pos != std::string::npos)
        file_path_ = src_file_path.substr(pos + 1);
    else
        file_path_ = src_file_path;
    OUTPUT_INFO("src:%s|file_name:%s", src_file_path.c_str(), file_path_.c_str());

    if (!out_file_name.empty())
        out_file_name_ = out_file_name;
    else
        out_file_name_ = file_path_.substr(0, file_path_.find_first_of('.'));

    COND_RET(out_file_name_.empty(), false);
    out_head_file_path_ = out_file_name_ + head_file_postfix_;
    out_cxx_file_path_  = out_file_name_ + cxx_file_postfix_;
    OUTPUT_INFO("output: %s, %s", out_head_file_path_.c_str(), out_cxx_file_path_.c_str());

    return true;
}

} // namespace pbc
