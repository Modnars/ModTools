/*
 * @Author: modnarshen
 * @Date: 2022/08/03 17:09:47
 * @LastEditors: modnarshen
 * @Description: 处理 protobuf 文件的通用接口
 */
#pragma once

// protobuf
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

namespace pb = google::protobuf;

static const std::size_t PB_POSTFIX_LEN = std::strlen(".proto");
static const std::size_t INDENT_SPACE_NUM = 4;
static const std::string LIMIT_COUNT_POSTFIX = "_COUNT";

enum ErrorCode {
    PROCESS_SUCCESS = 0,
    PROCESS_FAILURE = 1,
    PROCESS_NONE = 2,
};

class PbHandler {
public:
    PbHandler() { }
    virtual ~PbHandler() { }

public:
    // 依赖
    int for_each_dependency(const pb::FileDescriptor *file_desc);
    // 文件级别的枚举
    int for_each_enum(const pb::FileDescriptor *file_desc);
    // 类级别的枚举
    int for_each_enum(const pb::Descriptor *msg_desc);
    // message
    int for_each_message(const pb::FileDescriptor *file_desc);
    // nested msg
    int for_each_nested(const pb::Descriptor *msg_desc);

protected:
    // 依赖处理
    virtual int handle_dependency(const pb::FileDescriptor *file_desc, const pb::FileDescriptor *dep_desc) = 0;
    // 处理 package
    virtual int handle_package(const pb::FileDescriptor *file_desc) = 0;
    // 文件级别的枚举处理函数
    virtual int handle_enum(const pb::FileDescriptor *file_desc, const pb::EnumDescriptor *enum_desc) = 0;
    // 类级别的枚举处理函数
    virtual int handle_enum(const pb::Descriptor *msg_desc, const pb::EnumDescriptor *enum_desc) = 0;
    // message处理函数
    virtual int handle_message(const pb::FileDescriptor *file_desc, const pb::Descriptor *msg_desc) = 0;
    // nested处理函数
    virtual int handle_nested(const pb::Descriptor *msg_desc, const pb::Descriptor *nested_desc) = 0;
};
