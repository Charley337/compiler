#ifndef __ASSEMBLY_GENERATOR_H__
#define __ASSEMBLY_GENERATOR_H__

#include "lexer.h"

#define IN_MEM -1
#define REG_NUM 32
#define ASM_FILEPATH "assembly.asm"

typedef struct regval {
    char *val;
} regval;

class Assembly {
public:
    // 编码表（哈希表）
    map<string, int> *code_list;

    // 逆向编码表
    map<int, string> *code_reverse;

    map<string, symbol> *symbol_table;

    vector<ILitem> *intermediates;

    map<string, int> name_to_reg;

    regval regs[REG_NUM];

    FILE *fp_asm;

    Assembly(map<string, int> *codelist, map<int, string> *codereverse, map<string, symbol> *symtab, vector<ILitem> *interm);

    void assembly_generate();

    void init_nametoreg();

    void init_regs();

    int set_reg(int idx, char *name);

    int save_reg(int idx);

    int free_reg(int idx);

    int getreg();
};

#endif