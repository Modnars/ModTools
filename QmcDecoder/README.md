# QmcDecoder

QMC加密文件解析工具，提供“命令行”、“配置文件模式”和“GUI程序”三种解析方式。

## 支持文件格式

| # | 原文件格式 | 结果文件格式 |
|---| ---------- | ------------ |
| 1 | .qmc0      | .mp3         |
| 2 | .qmcogg    | .ogg         |
| 3 | .qmcflac   | .flac        |

## 使用方法

- 1. 命令行方式

```bash
# 解析config.txt中指定的源文件，并将结果文件存储至config.txt中指定的目标目录
# config.txt具体格式请参阅方式2
$ ./QmcDecoder config.txt

# 解析单个指定源文件，并将结果存储至目标目录
$ ./QmcDecoder source_file destination_dir
```

- 2. 配置文件方式

具体执行方式参阅方式1，其中config.txt格式如下:

```config.txt
# 使用`#`来注释单行，就像这样。
# inputFiles:
/Users/Modnar/Music/TestMusicFile.qmc0
/Users/Modnar/local/Music/AnotherTestMusicFile.qmc0

# 在`输入文件`和`输出目录`之间用空行分隔，就像上面这行这样。
# outputDir:
/Users/Modnar/Desktop/
/Users/Modnar/Desktop/Temp/
# 程序只会将结果文件存储至一个目标目录，故上面的Temp目录不会被写入结果文件。
```

- 3. GUI可执行程序

```bash
# 直接执行main.py即可
$ ./main.py
```

## 下载与安装

```bash
$ git clone git@github.com:Modnars/ModTools.git
$ cd ModTools/QmcDecoder/
$ make
```

## 补充说明

&#160; &#160; &#160; &#160; 请确保你拥有`GNU C++11`编译器，且对于GUI程序，请确保你安装了Python(默认3.7)。

> Author : Modnar
>
> Date: 2020/02/11
>
> Copyrights (c) 2020 Modnar. All rights reserved.
