# [编译原理] 类C语言编译器设计

## 1 模块说明

### 1.1 词法分析器

## 2 使用说明

### 2.1 文件目录

```c
.
├─bin				// 可执行文件目录
├─build				// cmake中间文件目录
├─design			// 设计文件目录
├─lab1				// 实验一（词法分析器）源代码目录
├─CMakeLists.txt	// 
├─main.cpp			// 程序入口，main函数
└─README.md			// 
```

### 2.2 编译方法

* 工具：

  cmake

  mingw

  make

* 编译步骤：

  * 在项目根目录新建 bin 和 build 两个文件夹：

    ```bash
    mkdir bin
    mkdir build
    ```

  * 进入到 ./build/ 目录中

    ```bash
    cd build
    ```

  * 执行下列代码：

    ```bash
    cmake .. -G "Unix Makefiles"
    make
    ```

* bash 文件参考（windows的.bat文件）：

  ```bash
  cd # 项目根目录
  rd /s/q build
  rd /s/q bin
  mkdir build
  mkdir bin
  cd build
  cmake .. -G "Unix Makefiles"
  make
  ```

### 2.3 使用方法

先把可执行文件路径加入 path 环境变量。

```bash
lexer # 源文件路径    例如: lexer src_file.c
```

结果输出 token.txt 和 symbol_table.txt 两个文件。

