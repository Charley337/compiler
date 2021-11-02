#ifndef __LEXER__H__
#define __LEXER__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include "cmd_font_style.h"
#include "flex_buffer.h"

using namespace std;

#define TOKEN_EOF -1
#define TOKEN_ERROR -2

#define CODE_LIST_FILEPATH "code_list.txt"
#define KEYWORD_SET_FILEPATH "keyword_set.txt"

typedef struct symbol {
    char *name;
    int type;
    int offset;
}symbol;

typedef struct token {
    int typecode;
    char *value;
}token;

class Lexer {
public:
    // 编码表（哈希表）
    map<string, int> code_list;

    // 逆向编码表
    map<int, string> code_reverse;

    // 关键字集合
    set<string> keywords_set;

    // 代码段缓冲区
    char *fbuf;
    long fbuf_len;
    long fbuf_beginning;
    long fbuf_forward;

    // token表
    vector<token> token_list;

    // 符号表
    map<string, symbol> symbol_table;

    Lexer(char *src);

    // 创建编码表（哈希表）
    void init_code_list();

    // 加载关键字集合
    void init_keywords_set();

    // 初始化token表
    void init_token_list();

    // 读源代码文件
    void read_src_file(char *filepath);

    // getch
    char getch();

    // 判断是不是数字
    static bool isdigit(char ch);

    // 判断是不是字母
    static bool isalpha(char ch);

    // 判断是不是十六进制
    bool ishex(char ch);

    // 判断是不是八进制
    bool isoctal(char ch);

    // 判断是不是二进制
    bool isbinary(char ch);

    // 判断是否为关键字
    bool iskeyword(char *tkn);

    // token
    token token_scan();

    // 插入符号表
    void symboltable_insert(char *name);

    // token 错误处理
    token error_handler();

    // 输出token.txt和symbolList.txt文件
    void output_files();

private:
    // 把截取的token复制出来
    char* copytoken();
};

#endif