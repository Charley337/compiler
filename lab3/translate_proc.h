#ifndef __TRANSLATE_PROC__H__
#define __TRANSLATE_PROC__H__

#include "lr1_analyser.h"

void free_symlist(SymList *symhead);
void* get_attr_val(SymNode *sym, const char* attr_name);

void proc_grammar_1(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_2(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_3(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_4(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_5(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_6(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_7(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_8(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_9(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_10(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_11(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_12(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_13(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_14(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_15(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_16(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_17(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_18(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_19(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_20(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_21(SymNode *symfather, SymList *symhead, Lexer *lex);
void proc_grammar_22(SymNode *symfather, SymList *symhead, Lexer *lex);

#endif
