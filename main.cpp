#include "lexer.h"
#include "lr1_analyser.h"

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
    LR1Analyser lr1analyser;
    ATindex index;
    index.table = AT_TABLE_ACTION;
    index.state = 21;
    index.symbol = "*";
    printf("type = %d, val = %d\n", lr1analyser.analyse_table.find(index)->second.type, lr1analyser.analyse_table.find(index)->second.val);
    for(int i = 0; i < lr1analyser.grammar_list_len; i++) {
        printf("%s\n", lr1analyser.grammar_list[i]);
    }

    // 程序结束
    printf(FONT_BLUE FONT_HIGHLIGHT"ending\n"RESET_STYLE);
    return 0;
}
