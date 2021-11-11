#include "translate_proc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_symlist(SymList *symhead) {
    SymList *p = symhead;
    SymList *pt = p;
    Attr *pa;
    Attr *pat;
    while (p != NULL) {
        p = p->next;
        pa = pt->sym.attr;
        pat = pa;
        while (pa != NULL) {
            pa = pa->next;
            free(pat->val);
            free(pat);
            pat = pa;
        }
        free(pt);
        pt = p;
    }
}

void* get_attr_val(SymNode *sym, const char* attr_name) {
    Attr *pattr = sym->attr;
    while (pattr != NULL) {
        if (strcmp(pattr->attr_name, attr_name) == 0) {
            return pattr->val;
        }
        pattr = pattr->next;
    }
    return NULL;
}

void proc_grammar_1(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 1\n");
    free_symlist(symhead);
}

void proc_grammar_2(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 2\n");
    free_symlist(symhead);
}

void proc_grammar_3(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 3\n");
    free_symlist(symhead);
}

void proc_grammar_4(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 4\n");
    char *type = (char*)get_attr_val(&(symhead->sym), "type");
    int type_id = lex->code_list.find(type)->second;
    int category_id = lex->code_list.find("val_name")->second;
    int sizeof_type = lex->sizeof_type.find(type)->second;
    map<string, symbol>::iterator ite;
    Attr *pa = symhead->next->sym.attr;
    while (pa != NULL) {
        if (strcmp(pa->attr_name, "name") == 0) {
            ite = lex->symbol_table.find((char*)pa->val);
            if (ite == lex->symbol_table.end()) {
                printf(FONT_RED FONT_HIGHLIGHT"val should be defined before using!\n"RESET_STYLE);
                exit(-1);
            }
            ite->second.type = type_id;
            ite->second.category = category_id;
            ite->second.offset = lex->offset;
            lex->offset += sizeof_type;
        }
        pa = pa->next;
    }
    free_symlist(symhead);
}

void proc_grammar_5(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 5\n");
    symfather->attr = (Attr*)malloc(sizeof(Attr));
    symfather->attr->next = NULL;
    symfather->attr->attr_name = "type";
    char *name = (char*)get_attr_val(&(symhead->sym), "name");
    symfather->attr->val = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy((char*)symfather->attr->val, name);
    free_symlist(symhead);
}

void proc_grammar_6(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 6\n");
    proc_grammar_5(symfather, symhead, lex);
}

void proc_grammar_7(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 7\n");
    proc_grammar_5(symfather, symhead, lex);
}

void proc_grammar_8(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 8\n");
    proc_grammar_5(symfather, symhead, lex);
}

void proc_grammar_9(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 9\n");
    char *name;
    symfather->attr = (Attr*)malloc(sizeof(Attr));
    symfather->attr->attr_name = "name";
    name = (char*)get_attr_val(&(symhead->sym), "name");
    symfather->attr->val = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy((char*)symfather->attr->val, name);
    Attr *fpa = symfather->attr;
    Attr *lpa = symhead->next->next->sym.attr;
    while (lpa != NULL) {
        if (strcmp(lpa->attr_name, "name") == 0) {
            fpa->next = (Attr*)malloc(sizeof(Attr));
            fpa->next->attr_name = "name";
            fpa->next->val = (char*)malloc(sizeof(char) * (strlen((char*)lpa->val) + 1));
            strcpy((char*)fpa->next->val, (char*)lpa->val);
            fpa = fpa->next;
        }
        lpa = lpa->next;
    }
    fpa->next = NULL;
    free_symlist(symhead);
}

void proc_grammar_10(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 10\n");
    symfather->attr = (Attr*)malloc(sizeof(Attr));
    symfather->attr->next = NULL;
    symfather->attr->attr_name = "name";
    char *name = (char*)get_attr_val(&(symhead->sym), "name");
    symfather->attr->val = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy((char*)symfather->attr->val, name);
    free_symlist(symhead);
}

void proc_grammar_11(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 11\n");
    free_symlist(symhead);
}

void proc_grammar_12(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 12\n");
    free_symlist(symhead);
}

void proc_grammar_13(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 13\n");
    free_symlist(symhead);
}

void proc_grammar_14(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 14\n");
    free_symlist(symhead);
}

void proc_grammar_15(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 15\n");
    free_symlist(symhead);
}

void proc_grammar_16(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 16\n");
    free_symlist(symhead);
}

void proc_grammar_17(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 17\n");
    free_symlist(symhead);
}

void proc_grammar_18(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 18\n");
    free_symlist(symhead);
}

void proc_grammar_19(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 19\n");
    free_symlist(symhead);
}

void proc_grammar_20(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 20\n");
    free_symlist(symhead);
}

void proc_grammar_21(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 21\n");
    free_symlist(symhead);
}

void proc_grammar_22(SymNode *symfather, SymList *symhead, Lexer *lex) {
    // printf("hello 22\n");
    free_symlist(symhead);
}
