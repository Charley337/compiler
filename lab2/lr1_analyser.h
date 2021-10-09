#ifndef __LR1_ANALYSER_H__
#define __LR1_ANALYSER_H__

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <stack>

using namespace std;

#define AT_COL_ACTION 0
#define AT_COL_GOTO 1

#define AT_TYPE_SHIFT 0
#define AT_TYPE_REDUCE 1
#define AT_TYPE_ACC 2
#define AT_TYPE_GOTO 3

typedef struct ATindex {
    int col;
    int state;
    char *symbol;
}ATindex;

typedef struct ATval {
    int type;
    int val;
}ATval;

class LR1Analyser {
public:
    // 分析表
    map<ATindex, ATval> analyse_table;

    // 状态栈
    stack<int> state_stack;

    // 符号栈
    stack<char*> symbol_stack;

    LR1Analyser();

    // 栈初始化
    void stack_init();

    // 分析表初始化
    void at_init();

private:

};

#endif
