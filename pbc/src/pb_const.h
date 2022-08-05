/*
 * @Author: modnarshen
 * @Date: 2022/05/18 17:41:02
 * @LastEditors: modnarshen
 * @Description: 工具主体功能
 */
#pragma once

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

#include "pb_handler.h"
#include "util/printer.h"
#include "util/singleton.h"

namespace pbc {

class ErrorCollector : public pb::compiler::MultiFileErrorCollector {
public:
    virtual void AddError(const std::string &filename, int line, int column, const std::string &message) {
        std::string err_location = filename + ":" + std::to_string(line) + ":" + std::to_string(column);
        errors_.emplace_back(err_location, message);
    }

    void PrintError() const {
        for (const auto &err : errors_)
            OUTPUT_ERROR("%s: %s", err.first.c_str(), err.second.c_str());
    }

private:
    std::vector<std::pair<std::string, std::string>> errors_;
};

class PbConst : public PbHandler, public Singleton<PbConst> {
public:
    PbConst();
    ~PbConst();

public:
    int Init(const std::string &src_file_path, const std::string &out_file_name = "");
    int Parse();

protected:
    // 依赖处理
    virtual int handle_dependency(const pb::FileDescriptor *file_desc, const pb::FileDescriptor *dep_desc) { return 0; }
    // 文件级别的枚举处理函数
    virtual int handle_enum(const pb::FileDescriptor *file_desc, const pb::EnumDescriptor *enum_desc) { return 0; }
    // 类级别的枚举处理函数
    virtual int handle_enum(const pb::Descriptor *msg_desc, const pb::EnumDescriptor *enum_desc) { return 0; }
    // message处理函数
    virtual int handle_message(const pb::FileDescriptor *file_desc, const pb::Descriptor *msg_desc) { return 0; }
    // nested处理函数
    virtual int handle_nested(const pb::Descriptor *msg_desc, const pb::Descriptor *nested_desc) { return 0; }

private:
    // proto file name
    std::string file_path_;          // example.proto
    std::string out_file_name_;      // example
    std::string out_head_file_path_; // example.pbc.h
    std::string out_cxx_file_path_;  // example.pbc.cc

    // cxx head, source file postfix
    std::string head_file_postfix_ = ".pbc.h";
    std::string cxx_file_postfix_ = ".pbc.cc";

    pb::compiler::DiskSourceTree src_tree_;
    pb::compiler::Importer *importer_ = nullptr;
    const pb::FileDescriptor *file_desc_ = nullptr;
    ErrorCollector error_collector_;
};
} // namespace pbc
