# _pbc_

<div align="center">
    <img src="https://user-images.githubusercontent.com/22772190/184528491-4c5b80f5-9b39-4bd7-9ab0-f24871e2c6cb.png" />
</div>

&#160; &#160; &#160; &#160; `pbc` 是一个基于 `protobuf` 实现的工具。它可以将 `protobuf` 定义的数据结构生成 `C 语言` 可支持的数据结构代码，并提供一系列必要的功能接口。可应用于 `protobuf` 数据映射到机器的共享内存等。此外，也可以用 `pbc` 来定义一些针对特定 `message` 的特殊逻辑代码，这些往往都是 `protobuf` 本身不会额外支持的功能。`pbc` 可以帮助用户更好地拓展使用 `protobuf` 定义的数据结构、更好地移植适配代码。

&#160; &#160; &#160; &#160; `pbc` 的工作方式与 `protobuf` 非常类似，通过 `pbc` 可以根据 `example.proto` 及其中必要的一些 `pbc` 命令得到相应的 `example.pbc.h` 及 `example.pbc.cc` 文件。接下来，就可以将这些源码 `#include` 进入项目工程代码，正确编译链接即可正常使用。至于 `pbc` 这个名字，可以从源码中理解为 `PbConst` 的缩写。事实上，我只是单纯地想叫它 `pbc` 而已，为了这个 `c` 开头的单词，我最终选择了 `const`。因为我认为 `const` 是 `C/C++` 程序员与编译器之间达成的一种默契与约定，用 `const` 来表示 `c`，实在是再合适不过了。

## 构建

&#160; &#160; &#160; &#160; `pbc` 依赖的 `protobuf` 版本是 `protobuf-3.7.0`。当然，`pbc` 中应用到的必要的 `protobuf` API 并不算很多，相信后续版本也会很好地支持这些必要的 API 接口功能。如果 `protobuf-3.7.0` 即可满足你的需求，可以直接解包 `3rd/protobuf-3.7.0.tar.gz` 来使用。当然，也可以使用其他版本的安装包，那么此时可能修改的还包括 `CMakeLists.txt` 中一些必要变量的设定值。下面给出 `protobuf-3.7.0` 版本的构建流程。

- 1 下载 `ModTools` 项目源码

```bash
% git clone https://github.com/Modnars/ModTools.git
```

- 2 解压缩 `protobuf-3.7.0.tar.gz` 数据包

```bash
% cd ModTools/pbc/3rd && tar -zxvf protobuf-3.7.0.tar.gz
```

- 3 构建 `pbc` 工具
```bash
% cd .. # From `3rd` to `pbc` directory
% ./build.sh
```

- 4 使用 `pbc` 工具
```bash
% ./build/pbc --help
```

## 用法

### 工具用法
```bash
% ./pbc --help
Usage: ./pbc [OPTION] PROTO_FILES
根据给定的选项对 PROTO_FILES 进行解析并输出相应内容:
  -IPATH, --proto_path=PATH  指定查询的 .proto 文件目录，如果 import 了文件，也要填充进来
  -o, --cpp_out              指定生成的 .pbc.h, .pbc.cc 文件输出目录
  -n, --file_name            按照给定的 file_name 来重新命名生成的 .pbc.h, .pbc.cc 文件名
  -v, --version              获取版本信息并退出
  -d, --debug                以 DEBUG 模式运行此程序，可获取更多程序运行信息
  -h, --help                 获取此帮助信息并退出
```

### `pbc` 命令关键字

| 关键词 | <div align="center">涵义与功能</div> |
| :-: | :- |
| `@pbc_declare` | 用于声明此 proto 文件需要生成相应的 pbc 源码，只有拥有 `@pbc_declare` 标识的文件才会生成 pbc 源码，相当于 **文件级开关**。 |
| `@pbc_node` | 用于声明此 message 需要生成相应的 pbc 源码，只有拥有 `@pbc_node` 标识的 message 才会生成 pbc 源码，相当于 **源码类级开关**。 |
| `@pbc_type` | 用于声明此字段生成为 pbc 源码时使用指定类型来生成。比如 protobuf 字段类型为 int32，但可以声明为 @pbc_type int8_t。 |
| `@pbc_code` | 用于插入自定义实现的代码，这段代码会直接复制到生成的 .pbc.h 文件中。 |
| `@pbc_len` | 用于声明 repeated 字段的最大长度。pbc 会按照此最大长度来指定相应大小的存储空间。 |
| `@pbc_fix` | 用于声明 bytes、string 字段的最大长度。pbc 会按照此固定长度来指定相应大小的存储空间。 |
| `@pbc_key` | 用于声明此字段作为 find 查询时的 key。此外，pbc 会尝试为指定为 key 的类型生成比较函数。 |

## 声明

&#160; &#160; &#160; &#160; `pbc` 是本人根据工作中使用的 `pbp` 工具重写的工具，其保留了 `pbp` 的核心功能。
