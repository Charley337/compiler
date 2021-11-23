#include "lexer.h"
#include "lr1_analyser.h"
#include "assembly_generator.h"

void show_intermediate_language();
// 显示编码表
void show_code_list(Lexer *le);
void show_code_reverse(Lexer *le);
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
void show_lex_intermediates(Lexer *le);


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
    show_intermediate_language();

    // 目标代码生成器
    printf(FONT_BLUE FONT_HIGHLIGHT"Assembly Generator begin...\n"RESET_STYLE);
    Assembly assm(&lex.code_list, &lex.code_reverse, &lex.symbol_table, &lex.intermediates);
    assm.assembly_generate();

    // 程序结束
    printf(FONT_BLUE FONT_HIGHLIGHT"ending\n"RESET_STYLE);
    return 0;
}

void show_lex_intermediates(Lexer *le) {
    for (ILitem it: le->intermediates) {
        if (strcmp(it.op, "assign") == 0) {
            printf("%s=%s\n", it.result, it.arg1);
        }
        else {
            printf("%s=%s%s%s\n", it.result, it.arg1, it.op, it.arg2);
        }
    }
}

void show_intermediate_language() {
    FILE *fp = fopen(IL_FILEPATH, "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT"fail to read intermediate_language.txt\n"RESET_STYLE);
        exit(-1);
    }
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
}

void show_code_list(Lexer *le) {
    for (map<string, int>::iterator it = le->code_list.begin(); it != le->code_list.end(); it++) {
        printf("%s: %d\n", it->first.c_str(), it->second);
    }
}

void show_code_reverse(Lexer *le) {
    for (map<int, string>::iterator it = le->code_reverse.begin(); it != le->code_reverse.end(); it++) {
        printf("%d: %s\n", it->first, it->second.c_str());
    }
}

void show_keywords_set(Lexer *le) {
    for (set<string>::iterator it = le->keywords_set.begin(); it != le->keywords_set.end(); it++) {
        printf("%s\n", (*it).c_str());
    }
}

void show_token_list(Lexer *le) {
    for (token tk: le->token_list) {
        printf("(%d, %s)\n", tk.typecode, tk.value);
    }
}

void show_symbol_table(Lexer *le) {
    for (map<string, symbol>::iterator it = le->symbol_table.begin(); it != le->symbol_table.end(); it++) {
        printf("%s: (%s, %d, %d, %d, %d)\n", it->first.c_str(), it->second.name, it->second.category, it->second.type, it->second.offset, it->second.attr);
    }
}

void show_analyse_table(LR1Analyser *lr) {
    for (map<ATindex, ATval>::iterator it = lr->analyse_table.begin(); it != lr->analyse_table.end(); it++) {
        printf("(%d, %d, %s): (%d, %d)\n", it->first.table, it->first.state, it->first.symbol, it->second.type, it->second.val);
    }
}

void show_grammar_list(LR1Analyser *lr) {
    for (int i = 1; i <= lr->grammar_list_len; i++) {
        printf("%d: %s\n", i, lr->grammar_list[i]);
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
    SymNode temp;
    stack<SymNode> temp_stack;
    while (lr->symbol_stack.empty() == false) {
        temp.id = lr->symbol_stack.top().id;
        temp.attr = lr->symbol_stack.top().attr;
        lr->symbol_stack.pop();
        temp_stack.push(temp);
    }
    while (temp_stack.empty() == false) {
        temp.id = temp_stack.top().id;
        temp.attr = temp_stack.top().attr;
        temp_stack.pop();
        lr->symbol_stack.push(temp);
        printf("%s\n", lr->lex->code_reverse.find(temp.id)->second);
    }
}

