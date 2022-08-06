/*
 * @Author: modnarshen
 * @Date: 2022/08/03 17:10:02
 * @LastEditors: modnarshen
 * @Description: 处理 protobuf 文件的通用接口 - 定义实现
 */
#include "pb_handler.h"
#include "util/macro.h"

int PbHandler::for_each_dependency(const pb::FileDescriptor *file_desc) {
    int ret = ErrorCode::PROCESS_SUCCESS;
    for (int i = 0; i < file_desc->dependency_count(); ++i) {
        const auto *dependency_desc = file_desc->dependency(i);
        ret = handle_dependency(file_desc, dependency_desc);
        COND_RET_ELOG(ret != ErrorCode::PROCESS_SUCCESS, ret,
                      "an error occurred while handling file's dependency|file:%s|dependency:%s",
                      file_desc->name().c_str(), dependency_desc->name().c_str());
    }
    return ret;
}

int PbHandler::for_each_enum(const pb::FileDescriptor *file_desc) {
    int ret = ErrorCode::PROCESS_SUCCESS;
    for (int i = 0; i < file_desc->enum_type_count(); ++i) {
        const auto *enum_desc = file_desc->enum_type(i);
        ret = handle_enum(file_desc, enum_desc);
        COND_RET_ELOG(ret != ErrorCode::PROCESS_SUCCESS, ret,
                      "an error occurred while handling file's enum|file:%s|enum:%s", file_desc->name().c_str(),
                      enum_desc->name().c_str());
    }
    return ret;
}

int PbHandler::for_each_enum(const pb::Descriptor *msg_desc) {
    int ret = ErrorCode::PROCESS_SUCCESS;
    for (int i = 0; i < msg_desc->enum_type_count(); ++i) {
        const auto *enum_desc = msg_desc->enum_type(i);
        ret = handle_enum(msg_desc, enum_desc);
        COND_RET_ELOG(ret != ErrorCode::PROCESS_SUCCESS, ret,
                      "an error occurred while handling message's enum|message:%s|enum:%s", msg_desc->name().c_str(),
                      enum_desc->name().c_str());
    }
    return ret;
}

int PbHandler::for_each_message(const pb::FileDescriptor *file_desc) {
    int ret = ErrorCode::PROCESS_SUCCESS;
    for (int i = 0; i < file_desc->message_type_count(); ++i) {
        const auto *msg_desc = file_desc->message_type(i);
        ret = handle_message(file_desc, msg_desc);
        // 允许不进行处理
        COND_RET_ELOG(ret != ErrorCode::PROCESS_SUCCESS && ret != ErrorCode::PROCESS_NONE, ret,
                      "an error occurred while handling file's message|file:%s|message:%s", file_desc->name().c_str(),
                      msg_desc->name().c_str());
    }
    return ret;
}

int PbHandler::for_each_nested(const pb::Descriptor *msg_desc) {
    int ret = ErrorCode::PROCESS_SUCCESS;
    for (int i = 0; i < msg_desc->nested_type_count(); ++i) {
        const auto *nested_desc = msg_desc->nested_type(i);
        ret = handle_nested(msg_desc, nested_desc);
        // 允许不进行处理
        COND_RET_ELOG(ret != ErrorCode::PROCESS_SUCCESS && ret != ErrorCode::PROCESS_NONE, ret,
                      "an error occurred while handling message's nested type|message:%s|nested:%s",
                      msg_desc->name().c_str(), nested_desc->name().c_str());
    }
    return ret;
}
