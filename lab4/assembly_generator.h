#ifndef __ASSEMBLY_GENERATOR_H__
#define __ASSEMBLY_GENERATOR_H__

#include "lexer.h"

#define IN_MEM -1
#define REG_NUM 32

typedef struct regval {
    char *val;
} regval;

class Assembly {
public:
    map<string, symbol> *symbol_table;

    vector<ILitem> *intermediates;

    map<string, int> name_to_reg;

    regval regs[REG_NUM];

    Assembly(map<string, symbol> *symtab, vector<ILitem> *interm);

    void assembly_generate();

    void init_nametoreg();

    void init_regs();

    int set_reg(int idx, char *name);

    int free_reg(int idx);

    int getreg();
};

#endif