#include "assembly_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Assembly::Assembly(map<string, int> *codelist, map<int, string> *codereverse, map<string, symbol> *symtab, vector<ILitem> *interm) {
    code_list = codelist;
    code_reverse = codereverse;
    symbol_table = symtab;
    intermediates = interm;
    init_opcodes();
    init_nametoreg();
    init_regs();
    init_assembly_calls();
}


void Assembly::init_assembly_calls() {
    void (*buf[])(Assembly*, ILitem) = {
        assembly_function_0,
        assembly_function_1,
        assembly_function_2,
        assembly_function_3,
        assembly_function_4
    };
    int num = 5;
    assembly_calls = (void(**)(Assembly*, ILitem))malloc(sizeof(void(*)(Assembly*, ILitem)) * num);
    for (int i = 0; i < num; i++) {
        assembly_calls[i] = buf[i];
    }
}


void Assembly::init_opcodes() {
    opcodes["assign"] = 0;
    opcodes["+"] = 1;
    opcodes["-"] = 2;
    opcodes["*"] = 3;
    opcodes["/"] = 4;
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


int Assembly::save_reg(int idx) {
    if (idx >= REG_NUM || idx < 0) {
        return -1;
    }
    if (regs[idx].val != NULL) {
        // 输出写回内存的汇编代码
        int offset = symbol_table->find(regs[idx].val)->second.offset;
        fprintf(fp_asm, "sw x%d, %d(x0)\n", idx, offset);

        name_to_reg.find(regs[idx].val)->second = IN_MEM;
        free(regs[idx].val);
        regs[idx].val = NULL;
    }
    return 0;
}


// int Assembly::free_reg(int idx) {
//     if (idx >= REG_NUM || idx < 0) {
//         return -1;
//     }
//     if (regs[idx].val != NULL) {
//         if (symbol_table->find(regs[idx].val)->second.category != code_list->find("temp_name")->second) {
//             return -1;
//         }
//         name_to_reg.find(regs[idx].val)->second = IN_MEM;
//         free(regs[idx].val);
//         regs[idx].val = NULL;
//     }
//     return 0;
// }


int Assembly::getreg() {
    static int cnt = 0;
    for (int i = 1; i < REG_NUM; i++) {
        if (regs[i].val == NULL) {
            return i;
        }
    }
    cnt = (cnt + 1) % REG_NUM;
    if (cnt == 0)
        cnt++;
    save_reg(cnt);
    return cnt;
}

int Assembly::getreg(int busy) {
    static int cnt = 0;
    for (int i = 1; i < REG_NUM; i++) {
        if (i == busy) {
            continue;
        }
        if (regs[i].val == NULL) {
            return i;
        }
    }
    cnt = (cnt + 1) % REG_NUM;
    while (cnt == 0 || cnt == busy)
        cnt++;
    save_reg(cnt);
    return cnt;
}


void Assembly::assembly_generate() {
    fp_asm = fopen(ASM_FILEPATH, "w");
    if (fp_asm == NULL) {
        printf("fail to open assembly.asm\n");
        exit(-1);
    }
    for (ILitem it: *intermediates) {
        assembly_calls[opcodes.find(it.op)->second](this, it);
    }
    fclose(fp_asm);
}


