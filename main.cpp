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
    // 程序结束
    printf(FONT_BLUE FONT_HIGHLIGHT"ending\n"RESET_STYLE);
    return 0;
}
