#include "lexer.h"
#include "lr1_analyser.h"

// 显示编码表
void show_code_list(Lexer *le);
// 显示关键字合集
void show_keywords_set(Lexer *le);
// 显示token表
void show_token_list(Lexer *le);
// 显示符号表
void show_symbol_table(Lexer *le);
// 显示分析表
void show_analyse_table(LR1Analyser *lr);
// 显示文法表
void show_grammar_list(LR1Analyser *lr);
// 显示状态栈
void show_state_stack(LR1Analyser *lr);
// 显示符号栈
void show_symbol_stack(LR1Analyser *lr);


int main(int argc, char **argv) {
    // 主程序开始
    printf(FONT_BLUE FONT_HIGHLIGHT"begin...\n"RESET_STYLE);
    // 处理argv
    if (argc != 2) {
        printf(FONT_RED FONT_HIGHLIGHT"input source file errors.   Stop.\n"RESET_STYLE);
        exit(0);
    }

    // 词法分析器
    printf(FONT_BLUE FONT_HIGHLIGHT"lexer begin...\n"RESET_STYLE);
    Lexer lex(argv[1]);
    lex.output_files();

    // LR1文法语法分析器
    printf(FONT_BLUE FONT_HIGHLIGHT"LR1 analyser begin...\n"RESET_STYLE);
    LR1Analyser lr1analyser(&lex);
    lr1analyser.lr1_start();
    show_state_stack(&lr1analyser);
    printf("\n");
    show_symbol_stack(&lr1analyser);
    printf("\n");

    // 程序结束
    printf(FONT_BLUE FONT_HIGHLIGHT"ending\n"RESET_STYLE);
    return 0;
}


void show_code_list(Lexer *le) {
    for (map<string, int>::iterator it = le->code_list.begin(); it != le->code_list.end(); it++) {
        printf("%s: %d\n", it->first, it->second);
    }
}

void show_keywords_set(Lexer *le) {

}

void show_token_list(Lexer *le) {

}

void show_symbol_table(Lexer *le) {

}

void show_analyse_table(LR1Analyser *lr) {
    for (map<ATindex, ATval>::iterator it = lr->analyse_table.begin(); it != lr->analyse_table.end(); it++) {
        printf("(%d, %d, %s): (%d, %d)\n", it->first.table, it->first.state, it->first.symbol, it->second.type, it->second.val);
    }
}

void show_grammar_list(LR1Analyser *lr) {
    for (int i = 0; i < lr->grammar_list_len; i++) {
        printf("%s\n", lr->grammar_list[i]);
    }
}

void show_state_stack(LR1Analyser *lr) {
    int temp;
    stack<int> temp_stack;
    while (lr->state_stack.empty() == false) {
        temp = lr->state_stack.top();
        lr->state_stack.pop();
        temp_stack.push(temp);
    }
    while (temp_stack.empty() == false) {
        temp = temp_stack.top();
        temp_stack.pop();
        lr->state_stack.push(temp);
        printf("%d\n", temp);
    }
}

void show_symbol_stack(LR1Analyser *lr) {
    char* temp;
    stack<char*> temp_stack;
    while (lr->symbol_stack.empty() == false) {
        temp = lr->symbol_stack.top();
        lr->symbol_stack.pop();
        temp_stack.push(temp);
    }
    while (temp_stack.empty() == false) {
        temp = temp_stack.top();
        temp_stack.pop();
        lr->symbol_stack.push(temp);
        printf("%s\n", temp);
    }
}

