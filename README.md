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
├─lab2				// 实验二（语法分析器）源代码目录
├─lab3				// 实验三（语义制导）源代码目录
├─lab4				// 实验四（目标代码生成器）源代码目录
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
  cd ..\bin
  compiler input_code.txt
  ```

### 2.3 使用方法

先把可执行文件路径加入 path 环境变量。

```bash
compiler # 源文件路径    例如: lexer src_file.c
```

结果输出 token.txt 和 symbolTable.txt 两个文件。



# 3 结果展示

* 源程序

  ```c
  int result;
  int ans;
  int a, b, c;
  float f;
  bool boolean;
  a = 8;
  b = 5;
  c = 3;
  result = a * b + ( a - b ) + c;
  ans = (a - b) + (a - c) + (a - c);
  
  ```

* 运行截图

![image-20211123225757061](.\img\image-20211123225757061.png)

* 中间代码

  ```
  a=8
  b=5
  c=3
  t1=a*b
  t2=a-b
  t3=t1+t2
  t4=t3+c
  result=t4
  t5=a-b
  t6=a-c
  t7=t5+t6
  t8=a-c
  t9=t7+t8
  ans=t9
  
  ```

* 目标代码

  ```assembly
  addi x1, x0, 8
  addi x2, x0, 5
  addi x3, x0, 3
  add x4, x0, x1
  mul x4, x4, x2
  add x5, x0, x1
  sub x5, x5, x2
  add x6, x0, x4
  add x6, x6, x5
  add x7, x0, x6
  add x7, x7, x3
  add x8, x0, x7
  add x9, x0, x1
  sub x9, x9, x2
  add x10, x0, x1
  sub x10, x10, x3
  add x11, x0, x9
  add x11, x11, x10
  add x12, x0, x1
  sub x12, x12, x3
  add x13, x0, x11
  add x13, x13, x12
  add x14, x0, x13
  
  ```

