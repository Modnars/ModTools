/*
 * @Author: modnarshen
 * @Date: 2022/05/18 17:41:02
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

#include "pbc_printer.h"
#include "util/singleton.h"

namespace pb          = google::protobuf;
namespace pb_compiler = google::protobuf::compiler;

namespace pbc {
class PbConst : public Singleton<PbConst> {
public:
    bool Init(const std::string &src_file_path, const std::string &out_file_name = "");

private:
    // proto file name
    std::string file_path_;          // example.proto
    std::string out_file_name_;      // example
    std::string out_head_file_path_; // example.pbc.h
    std::string out_cxx_file_path_;  // example.pbc.cc

    // cxx head, source file postfix
    std::string head_file_postfix_ = ".pbc.h";
    std::string cxx_file_postfix_  = ".pbc.cc";

    pb_compiler::DiskSourceTree src_tree_;
    pb_compiler::Importer *importer_;
    const pb::FileDescriptor *file_desc_;
};
} // namespace pbc
