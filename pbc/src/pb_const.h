/*
 * @Author: modnarshen
 * @Date: 2022/05/18 17:41:02
 * @LastEditors: modnarshen
 * @Description: 工具主体功能
 */
#pragma once

#include <functional>

#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.h>

#include "pb_handler.h"
#include "util/printer.h"
#include "util/singleton.h"

namespace pbc {

struct type_convert {
    int pb_cpp_type;
    std::string cpp_type;
};

static const std::vector<type_convert> type_vector{
    {0, ""},
    {pb::FieldDescriptor::CPPTYPE_INT32, "int32_t"},
    {pb::FieldDescriptor::CPPTYPE_INT64, "int64_t"},
    {pb::FieldDescriptor::CPPTYPE_UINT32, "uint32_t"},
    {pb::FieldDescriptor::CPPTYPE_UINT64, "uint64_t"},
    {pb::FieldDescriptor::CPPTYPE_DOUBLE, "double"},
    {pb::FieldDescriptor::CPPTYPE_FLOAT, "float"},
    {pb::FieldDescriptor::CPPTYPE_BOOL, "bool"},
    {pb::FieldDescriptor::CPPTYPE_ENUM, "uint32_t"},
    {pb::FieldDescriptor::CPPTYPE_STRING, "char"},
    {pb::FieldDescriptor::CPPTYPE_MESSAGE, ""},
};

class ErrorCollector : public pb::compiler::MultiFileErrorCollector {
public:
    virtual void AddError(const std::string &filename, int line, int column, const std::string &message) override {
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
    PbConst() : importer_(nullptr), file_desc_(nullptr) { }
    ~PbConst();

public:
    // NOTES:
    //   filepath:  source/example.proto
    //   file_path: source/
    //   filename:  example.proto
    //   file_name: example
    // 总会有人 GET 到我的点 :)

    int Init(const std::string &proto_filepath, const std::vector<std::string> &proto_file_path,
             const std::string &out_file_path, const std::string &out_file_name);
    int Parse();

protected:
    // 依赖处理
    virtual int handle_dependency(const pb::FileDescriptor *file_desc, const pb::FileDescriptor *dep_desc) override;
    // 处理 package
    virtual int handle_package(const pb::FileDescriptor *file_desc) override;
    // 文件级别的枚举处理函数
    virtual int handle_enum(const pb::FileDescriptor *file_desc, const pb::EnumDescriptor *enum_desc) override;
    // 类级别的枚举处理函数
    virtual int handle_enum(const pb::Descriptor *msg_desc, const pb::EnumDescriptor *enum_desc) override;
    // message处理函数
    virtual int handle_message(const pb::FileDescriptor *file_desc, const pb::Descriptor *msg_desc) override;
    // nested处理函数
    virtual int handle_nested(const pb::Descriptor *msg_desc, const pb::Descriptor *nested_desc) override;

private:
    // Init 时执行的一些检查逻辑
    int CheckOnInit() const;
    // 检查文件是否生成代码
    bool CheckFileAndGetDeclarationCode(const pb::FileDescriptor *file_desc, std::string &code_block) const;
    // 检查 message 是否生成代码
    bool CheckMessageAndGetComment(const pb::Descriptor *msg_desc, std::string &comment) const;
    // 检查 message 所依赖的 message 是否生成代码
    bool CheckMessageDependency(const pb::Descriptor *msg_desc, std::string *err_msg) const;
    // 检查 field 的属性参数是否合法
    bool CheckFieldProperties(const pb::Descriptor *msg_desc) const;

private:
    // 通用命令字处理
    static int handle_common_cmd(const std::string &cmd, std::string &src, std::string &attachment);
    // namespace 使用 "::" 来分层
    void push_namespace(std::string &ns, const std::string &add_ns);
    // 获取 proto 中 message 名转换成的结构体名称
    std::string get_type_name(const std::string &proto_type_name) const;
    // 获取 cpp 的类型名
    std::string get_field_type_name(const pb::FieldDescriptor *field_desc, const std::string &custom_type) const;
    // 设定 repeated 结构的长度限制值
    void set_repeated_limit_value(const std::string &field_name, const std::string &value);
    // 获取 repeated 结构的长度限制名称
    std::string get_repeated_limit(const std::string &field_name) const;
    // 获取 repeated 结构的长度限制值
    std::string get_repeated_limit_value(const std::string &field_name) const;

private:
    // 将数据流写入文件
    int write_file(std::stringstream &ss, const std::string &filepath) const;

protected:
    /* ********** 生成函数相关 ********** */
    // 生成类的自定义代码
    void generate_class_pbc_code(const pb::Descriptor *msg_desc);
    // 生成枚举
    int generate_enum(const pb::EnumDescriptor *enum_desc, std::stringstream &ss, int indent_num);
    // 生成成员变量
    int generate_member_var(const pb::Descriptor *msg_desc);
    // 生成构造函数
    int generate_construct_func(const pb::Descriptor *msg_desc);
    // 生成 Clean 函数
    int generate_clean_func(const pb::Descriptor *msg_desc);
    // 生成 FromPb 函数
    int generate_frompb_func(const pb::Descriptor *msg_desc);
    // 生成 ToPb 函数
    int generate_topb_func(const pb::Descriptor *msg_desc);
    // 普通结构的 get 函数
    int generate_get_func(const pb::Descriptor *msg_desc);
    // 普通结构的 set 函数
    int generate_set_func(const pb::Descriptor *msg_desc);
    // repeated 结构的 size 函数
    int generate_repeated_size_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 get 函数
    int generate_repeated_get_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 set 函数
    int generate_repeated_set_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 Add 函数
    int generate_repeated_add_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 Del 函数
    int generate_repeated_del_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 DelByKey 函数
    int generate_repeated_del_by_key_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 DelBatch 函数
    int generate_repeated_del_batch_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 FindByKey 函数
    int generate_repeated_find_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 Swap 函数
    int generate_repeated_swap_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 is_full 函数
    int generate_repeated_full_func(const pb::Descriptor *msg_desc);
    // 为所有 repeated 结构生成 is_empty 函数
    int generate_repeated_empty_func(const pb::Descriptor *msg_desc);
    // 为所有定义了 key 命令的结构生成 eq_key 和 eq_ref 函数，如果有定义的话
    int generate_key_compare_func(const pb::Descriptor *msg_desc);
    // 为所有整形添加和减函数，默认 +1
    int generate_inc_and_dec_func(const pb::Descriptor *msg_desc);
    // 为所有成员变量生成 clear 函数
    int generate_clear_member_func(const pb::Descriptor *msg_desc);
    // 生成 ShortDebugString 函数
    int generate_debugstring_func(const pb::Descriptor *msg_desc);

    /* ********** 注释相关 ********** */
    // 通用 field 注释的处理函数，能处理 message field 和 enum value
    // @param loc[IN] 跟 field 或者 value 对应的 SourceLocation
    // @param cmds[OUT] 以命令字为 key，attachment 为 value 的 map
    // @param leading_comment[OUT] 前置注释
    // @param trailing_comment[OUT] 后置注释
    // @param indent_num[IN] 缩进，只用于生成注释
    int handle_field_comment(const pb::SourceLocation &loc, std::map<std::string, std::string> &cmds,
                             std::string &leading_comment, std::string &trailing_comment, int indent_num) const;

    // 注释通用处理，处理注释的入口
    // @param src[IN/OUT] 与 field 相关的前置或者后置注释，处理后会删掉命令行
    // @param cmds[OUT] 以命令字或者 "comment" 为 key，attachment 为 value 的 map
    // @param indent_num[IN] 缩进，只用于生成的注释
    int handle_comment(std::string &src, std::map<std::string, std::string> &cmds, int indent_num) const;

    // 将注释内容处理成为注释块
    // @param context[IN] 单行或者多行的注释内容
    // @param comment[OUT] 标准 C++ 注释，单行使用 one-line comment，多行使用 block comment
    // @param indent_num[IN] 缩进，1 indent_num == 4 * space
    // @param one_line[IN] 在proto文件中是否是 one-line comment
    int generate_comment(const std::string &context, std::string &comment, int indent_num, bool is_one_line) const;

private:
    // example: $ pbc --proto_path=PATH --cpp_out=OUT_DIR --file_name=FILE_NAME source/example.proto
    std::string proto_filename_;                   // example.proto
    std::string out_file_path_;                    // OUT_DIR 输出路径
    std::string out_file_name_;                    // FILE_NAME 生成文件名称（不包括拓展名）
    std::string out_hd_filepath_;                  // OUT_DIR/FILE_NAME.pbc.h
    std::string out_cc_filepath_;                  // OUT_DIR/FILE_NAME.pbc.cc
    std::string out_hd_file_postfix_ = ".pbc.h";   // 头文件后缀
    std::string out_cc_file_postfix_ = ".pbc.cc";  // 源码文件后缀
    std::vector<std::string> proto_paths_;         // 被包含 proto 的路径以及当前路径

    std::stringstream ss_hd_;           // 头文件输出流
    std::stringstream ss_cc_;           // 源码文件输出流
    std::stringstream ss_pbc_code_;     // @pbc_code 命令生成的源码汇总
    std::stringstream ss_declaration_;  // 声明内容
    std::stringstream ss_enum_;         // 枚举内容
    std::stringstream ss_struct_def_;   // 结构体声明
    std::stringstream ss_eq_key_def_;   // 结构体 eq_key 的比较函数代码
    std::stringstream ss_ref_key_def_;  // 结构体 ref_key 的比较函数代码
    std::string eq_key_args_;           // eq_key 的参数

    std::string pbc_namespace_;      // 生成代码的命名空间
    std::string message_namespace_;  // proto 的命名空间
    std::size_t namespace_num_;      // 命名空间数量
    std::unordered_map<std::string, std::string> repeated_limit_value_map_;

    pb::compiler::DiskSourceTree src_tree_;
    pb::compiler::Importer *importer_ = nullptr;
    const pb::FileDescriptor *file_desc_ = nullptr;
    ErrorCollector error_collector_;

private:
    // pbc 命令回调
    // 默认处理规则是从 src 中取出 cmd 与 attachment，并把剩下的 src 原样返回
    // @param cmd[IN] 命令字
    // @param src[IN/OUT] 输出取出绑定 cmd 后的 src
    // @param attachment[OUT] 与 cmd 相关的参数，无参数则为空
    // @return 找到绑定的 cmd 时返回零，否则返回非零值
    using CmdHandler = std::function<int(const std::string &cmd, std::string &src, std::string &attachment)>;
    static std::map<std::string, CmdHandler> cmd_handler_map_;
};
}  // namespace pbc
