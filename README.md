# Math Expression Parser

一个用 C++ 手写的数学表达式解析器，支持变量、自定义函数、注释和文件输入，适合学习编译原理的词法分析和递归下降语法分析。

## 功能

- 词法分析（Tokenizer）  
  将表达式字符串分割为 Token，支持数字、标识符、运算符、括号、注释（`#` 开头）

- 递归下降语法分析  
  构建抽象语法树（AST），正确处理优先级和结合性：
  - 加减（左结合）
  - 乘除（左结合）
  - 幂运算（右结合）
  - 一元负号
  - 括号
  - 内置函数调用

- 内置函数  
  `sgn`, `abs`, `sin`, `cos`, `tan`, `exp`, `log`, `arcsin`, `arccos`, `arctan`

- 变量支持  
  通过 `$var1=value1,var2=value2$` 在表达式文件中预定义，也可在代码中硬编码

- 交互式命令行  
  支持三个命令：
  - `ls` – 列出 `./formula/` 目录下的所有公式文件
  - `run <filename>` – 解析并计算 `./formula/` 中的公式文件
  - `debug <filename>` – 仅做词法分析，输出所有 Token 信息

- 公式文件格式
$这里是变量声明,必须在函数体之前$
函数定义

## 项目结构
MATHEXPRESSION/
├── src/
│ └── main.cpp # 源代码
├── formula/ # 公式文件目录
│ └── example.txt
├── README.md
└── LICENSE

## 编译与运行

### 环境要求
- C++ 编译器（支持 C++98/C++11）
- Linux / macOS / Windows（需做少量移植调整）
- 依赖库：标准库 + `<cmath>`

### 编译
```bash
g++ src/main.cpp -o math_parser -lm
