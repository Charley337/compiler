#ifndef __LR1_ANALYSER_H__
#define __LR1_ANALYSER_H__

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <stack>
#include <string.h>
#include "cmd_font_style.h"
#include "lexer.h"

using namespace std;

#define AT_TABLE_ACTION 0
#define AT_TABLE_GOTO 1

#define AT_TYPE_SHIFT 0
#define AT_TYPE_REDUCE 1
#define AT_TYPE_ACC 2
#define AT_TYPE_GOTO 3

typedef struct ATindex {
    int table;
    int state;
    int symbol;

    bool operator < (const ATindex &o) const {
		return table < o.table || (table == o.table && state < o.state) || (table == o.table && state == o.state && symbol < o.symbol);
	}
}ATindex;

typedef struct ATval {
    int type;
    int val;
}ATval;

typedef struct RowCol {
    int row;
    int col;

    bool operator < (const RowCol &o) const {
		return row < o.row || (row == o.row && col < o.col);
	}
}RowCol;

typedef struct SymNode {
    int id;
    Attr *attr;
}SymNode;

typedef struct SymList {
    SymNode sym;
    struct SymList *next;
}SymList;

class LR1Analyser {
public:
    Lexer *lex;

    // LR1.csv 转化过来的中间数据结构
    map<RowCol, char*> lr1_table;

    // 分析表
    map<ATindex, ATval> analyse_table;

    // 文法表
    char **grammar_list;
    int grammar_list_len;
    // 文法查找表
    map<string, int> grammar_reverse;

    // 状态栈
    stack<int> state_stack;

    // 符号栈
    stack<SymNode> symbol_stack;

    // token的游标
    vector<token>::iterator token_it;

    // 语义子函数指针数组
    void (**proc_list)(SymNode*, SymList*, Lexer*);
    int proc_num;

    LR1Analyser(Lexer *le);

    // 子函数指针数组初始化
    void proc_list_init();

    // 栈初始化
    void stack_init();

    // 分析表初始化
    void at_init();

    // 文法表初始化
    void grammar_list_init();

    // 从缓冲区中读出一行，如果成功返回1，读到缓冲区末尾返回0
    static int get_line(char *line, char *buffer, int *bp);

    // 从一行中取出列值
    static int get_value(char *val, char *line, int *lp);

    // 从类似 shift 10 中取出数字
    int get_digit_from_value(char *val);

    // 语法分析开始
    void lr1_start();

    // 移进
    void shift_action();

    void shift_goto();

    // 归约
    void reduce(int val);

    // 接受
    void accept();

    // 出错 
    void error_handle();

private:

};

#endif
