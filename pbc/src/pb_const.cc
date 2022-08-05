/*
 * @Author: modnarshen
 * @Date: 2022/05/18 17:41:09
 * @LastEditors: modnarshen
 * @Description: 工具主体功能 定义实现
 */
#include "pb_const.h"
#include "util/macro.h"
#include "util/string.h"

namespace pbc {
PbConst::PbConst() : importer_(nullptr), file_desc_(nullptr) {
}

PbConst::~PbConst() {
    if (importer_)
        delete importer_;
}

int PbConst::Init(const std::string &src_file_path, const std::string &out_file_name) {
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
    out_cxx_file_path_ = out_file_name_ + cxx_file_postfix_;
    OUTPUT_INFO("output: %s, %s", out_head_file_path_.c_str(), out_cxx_file_path_.c_str());

    src_tree_.MapPath("", "./"); // 默认加入当前目录
    importer_ = new pb::compiler::Importer(&src_tree_, &error_collector_);
    COND_RET_ELOG(!importer_, ErrorCode::ERR_INIT_FAILED, "init importer failed");

    file_desc_ = importer_->Import(file_path_);
    if (nullptr == file_desc_) {
        OUTPUT_ERROR("cannot open proto file|file:%s", file_path_.c_str());
        error_collector_.PrintError();
        return ErrorCode::ERR_INIT_FAILED;
    }

    return ErrorCode::SUCCESS;
}

int PbConst::Parse() {
    return ErrorCode::SUCCESS;
}

} // namespace pbc
