#include "translate_proc.h"
#include <stdio.h>
#include <stdlib.h>

void free_symlist(SymList *symhead) {
    SymList *p = symhead;
    SymList *pt = p;
    while (p != NULL) {
        p = p->next;
        free(pt);
        pt = p;
    }
}

void proc_grammar_1(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 1\n");
    free_symlist(symhead);
}

void proc_grammar_2(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 2\n");
    free_symlist(symhead);
}

void proc_grammar_3(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 3\n");
    free_symlist(symhead);
}

void proc_grammar_4(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 4\n");
    free_symlist(symhead);
}

void proc_grammar_5(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 5\n");
    free_symlist(symhead);
}

void proc_grammar_6(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 6\n");
    free_symlist(symhead);
}

void proc_grammar_7(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 7\n");
    free_symlist(symhead);
}

void proc_grammar_8(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 8\n");
    free_symlist(symhead);
}

void proc_grammar_9(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 9\n");
    free_symlist(symhead);
}

void proc_grammar_10(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 10\n");
    free_symlist(symhead);
}

void proc_grammar_11(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 11\n");
    free_symlist(symhead);
}

void proc_grammar_12(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 12\n");
    free_symlist(symhead);
}

void proc_grammar_13(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 13\n");
    free_symlist(symhead);
}

void proc_grammar_14(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 14\n");
    free_symlist(symhead);
}

void proc_grammar_15(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 15\n");
    free_symlist(symhead);
}

void proc_grammar_16(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 16\n");
    free_symlist(symhead);
}

void proc_grammar_17(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 17\n");
    free_symlist(symhead);
}

void proc_grammar_18(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 18\n");
    free_symlist(symhead);
}

void proc_grammar_19(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 19\n");
    free_symlist(symhead);
}

void proc_grammar_20(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 20\n");
    free_symlist(symhead);
}

void proc_grammar_21(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 21\n");
    free_symlist(symhead);
}

void proc_grammar_22(SymNode *symfather, SymList *symhead, Lexer *lex) {
    printf("hello 22\n");
    free_symlist(symhead);
}
