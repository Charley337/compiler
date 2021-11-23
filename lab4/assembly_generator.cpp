#include "assembly_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Assembly::Assembly(map<string, symbol> *symtab, vector<ILitem> *interm) {
    symbol_table = symtab;
    intermediates = interm;
    init_nametoreg();
    init_regs();
}


void Assembly::init_nametoreg() {
    for (map<string, symbol>::iterator it = symbol_table->begin(); it != symbol_table->end(); it++) {
        name_to_reg[it->first] = IN_MEM;
    }
}


void Assembly::init_regs() {
    for (int i = 0; i < REG_NUM; i++) {
        regs[i].val = NULL;
    }
}


int Assembly::set_reg(int idx, char *name) {
    if (idx >= REG_NUM || idx < 0) {
        return -1;
    }
    if (name_to_reg.find(name) == name_to_reg.end()) {
        return -1;
    }
    name_to_reg.find(name)->second = idx;
    regs[idx].val = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(regs[idx].val, name);
    return 0;
}


int Assembly::free_reg(int idx) {
    if (idx >= REG_NUM || idx < 0) {
        return -1;
    }
    if (regs[idx].val != NULL) {
        // TODO: 输出写回内存的汇编代码


        name_to_reg.find(regs[idx].val)->second = IN_MEM;
        free(regs[idx].val);
        regs[idx].val = NULL;
    }
    return 0;
}

int Assembly::getreg() {
    for (int i = 0; i < REG_NUM; i++) {
        if (regs[i].val == NULL) {
            return i;
        }
    }
    free_reg(0);
    return 0;
}


void Assembly::assembly_generate() {
    
}
