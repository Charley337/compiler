#include "lr1_analyser.h"

LR1Analyser::LR1Analyser() {
    at_init();
    stack_init();
}


// 栈初始化
void LR1Analyser::stack_init() {
    // 先清空
    while (!state_stack.empty()) {
        state_stack.pop();
    }
    while (!symbol_stack.empty()) {
        symbol_stack.pop();
    }
    // 初始化
    state_stack.push(0);
    char *temp = (char*)malloc(sizeof(char) * 2);
    temp[0] = '#';
    temp[1] = '\0';
    symbol_stack.push(temp);
}


void LR1Analyser::at_init() {

}

