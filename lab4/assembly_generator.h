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

    map<string, int> opcodes;

    void (**assembly_calls)(Assembly*, ILitem);

    FILE *fp_asm;

    Assembly(map<string, int> *codelist, map<int, string> *codereverse, map<string, symbol> *symtab, vector<ILitem> *interm);

    void assembly_generate();

    void init_nametoreg();

    void init_regs();

    void init_opcodes();

    void init_assembly_calls();

    int set_reg(int idx, char *name);

    int save_reg(int idx);

    int free_reg(int idx);

    int getreg();
    int getreg(int busy);
};


void assembly_function_0(Assembly* assm, ILitem it);
void assembly_function_1(Assembly* assm, ILitem it);
void assembly_function_2(Assembly* assm, ILitem it);
void assembly_function_3(Assembly* assm, ILitem it);
void assembly_function_4(Assembly* assm, ILitem it);


#endif