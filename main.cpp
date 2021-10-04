#include "lexer.h"

int main(int argc, char **argv) {
    printf(FONT_BLUE FONT_HIGHLIGHT"begin...\n"RESET_STYLE);
    printf(FONT_BLUE"lexer begin...\n"RESET_STYLE);
    // 处理argv
    if (argc == 1) {
        printf(FONT_RED FONT_HIGHLIGHT"there is no src file input!\n"RESET_STYLE);
        exit(0);
    }

    Lexer lex(argv[1]);

    printf("try to open token.txt\n");
    FILE *fp = fopen("token.txt", "w");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT"fail to open token.txt\n"RESET_STYLE);
        exit(0);
    }
    int i = 1;
    for (vector<token>::iterator ite = lex.token_list.begin(); ite != lex.token_list.end(); ite++) {
        fprintf(fp, "(%2d, %s)\n", ite->typecode, ite->value);
        printf("it has already written [%d]\r", i);
        i++;
    }
    printf("\n");
    fclose(fp);
    printf("close token.txt\n");

    printf("try to open symbol_table.txt\n");
    fp = fopen("symbol_table.txt", "w");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT"fail to open symbol_table.txt\n"RESET_STYLE);
        exit(0);
    }
    i = 1;
    for (map<string, symbol>::iterator ite = lex.symbol_table.begin(); ite != lex.symbol_table.end(); ite++) {
        fprintf(fp, "(%s, %d, %d)\n", ite->second.name, ite->second.type, ite->second.offset);
        printf("it has already written [%d]\r", i);
        i++;
    }
    printf("\n");
    fclose(fp);
    printf("close symbol_table.txt\n");

    printf(FONT_BLUE FONT_HIGHLIGHT"ending\n"RESET_STYLE);
    return 0;
}
