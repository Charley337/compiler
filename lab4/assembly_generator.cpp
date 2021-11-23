#include "assembly_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Assembly::Assembly(map<string, int> *codelist, map<int, string> *codereverse, map<string, symbol> *symtab, vector<ILitem> *interm) {
    code_list = codelist;
    code_reverse = codereverse;
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


int Assembly::save_reg(int idx) {
    if (idx >= REG_NUM || idx < 0) {
        return -1;
    }
    if (regs[idx].val != NULL) {
        // 输出写回内存的汇编代码
        int offset = symbol_table->find(regs[idx].val)->second.offset;
        fprintf(fp_asm, "ST [%d], R%d\n", offset, idx);

        name_to_reg.find(regs[idx].val)->second = IN_MEM;
        free(regs[idx].val);
        regs[idx].val = NULL;
    }
    return 0;
}


int Assembly::free_reg(int idx) {
    if (idx >= REG_NUM || idx < 0) {
        return -1;
    }
    if (regs[idx].val != NULL) {
        if (symbol_table->find(regs[idx].val)->second.category != code_list->find("temp_name")->second) {
            return -1;
        }
        name_to_reg.find(regs[idx].val)->second = IN_MEM;
        free(regs[idx].val);
        regs[idx].val = NULL;
    }
    return 0;
}


int Assembly::getreg() {
    static int cnt = 0;
    for (int i = 0; i < REG_NUM; i++) {
        if (regs[i].val == NULL) {
            return i;
        }
    }
    cnt = (cnt + 1) % REG_NUM;
    save_reg(cnt);
    return cnt;
}


void Assembly::assembly_generate() {
    fp_asm = fopen(ASM_FILEPATH, "w");
    if (fp_asm == NULL) {
        printf("fail to open assembly.asm\n");
        exit(-1);
    }
    int regid1;
    int regid2;
    for (ILitem it: *intermediates) {
        if (name_to_reg.find(it.arg1) == name_to_reg.end()) {
            regid1 = getreg();
            fprintf(fp_asm, "LD R%d, %d\n", regid1, atoi(it.arg1));
        }
        else 
            regid1 = name_to_reg.find(it.arg1)->second;
        if (strcmp(it.op, "assign") != 0) {
            regid2 = name_to_reg.find(it.arg2)->second;
        }

        if (strcmp(it.op, "+") == 0) {
            if (regid1 == IN_MEM) {
                regid1 = getreg();
                set_reg(regid1, it.arg1);
                name_to_reg.find(it.arg1)->second = regid1;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid1, symbol_table->find(it.arg1)->second.offset);
            }
            if (regid2 == IN_MEM) {
                regid2 = getreg();
                set_reg(regid2, it.arg2);
                name_to_reg.find(it.arg2)->second = regid2;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid2, symbol_table->find(it.arg2)->second.offset);
            }
            if (regid1 == regid2) {
                printf("panic!\n");
                exit(-1);
            }
            if (name_to_reg.find(it.result)->second != IN_MEM) {
                free_reg(name_to_reg.find(it.result)->second);
            }
            name_to_reg.find(it.arg1)->second = IN_MEM;
            set_reg(regid1, it.result);
            name_to_reg.find(it.result)->second = regid1;
            fprintf(fp_asm, "LD [%d], R%d\n", symbol_table->find(it.arg1)->second.offset, regid1);
            fprintf(fp_asm, "ADD R%d, R%d, R%d\n", regid1, regid1, regid2);
        }
        else if (strcmp(it.op, "-") == 0) {
            if (regid1 == IN_MEM) {
                regid1 = getreg();
                set_reg(regid1, it.arg1);
                name_to_reg.find(it.arg1)->second = regid1;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid1, symbol_table->find(it.arg1)->second.offset);
            }
            if (regid2 == IN_MEM) {
                regid2 = getreg();
                set_reg(regid2, it.arg2);
                name_to_reg.find(it.arg2)->second = regid2;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid2, symbol_table->find(it.arg2)->second.offset);
            }
            if (regid1 == regid2) {
                printf("panic!\n");
                exit(-1);
            }
            if (name_to_reg.find(it.result)->second != IN_MEM) {
                free_reg(name_to_reg.find(it.result)->second);
            }
            name_to_reg.find(it.arg1)->second = IN_MEM;
            set_reg(regid1, it.result);
            name_to_reg.find(it.result)->second = regid1;
            fprintf(fp_asm, "LD [%d], R%d\n", symbol_table->find(it.arg1)->second.offset, regid1);
            fprintf(fp_asm, "SUB R%d, R%d, R%d\n", regid1, regid1, regid2);
        }
        else if (strcmp(it.op, "*") == 0) {
            if (regid1 == IN_MEM) {
                regid1 = getreg();
                set_reg(regid1, it.arg1);
                name_to_reg.find(it.arg1)->second = regid1;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid1, symbol_table->find(it.arg1)->second.offset);
            }
            if (regid2 == IN_MEM) {
                regid2 = getreg();
                set_reg(regid2, it.arg2);
                name_to_reg.find(it.arg2)->second = regid2;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid2, symbol_table->find(it.arg2)->second.offset);
            }
            if (regid1 == regid2) {
                printf("panic!\n");
                exit(-1);
            }
            if (name_to_reg.find(it.result)->second != IN_MEM) {
                free_reg(name_to_reg.find(it.result)->second);
            }
            name_to_reg.find(it.arg1)->second = IN_MEM;
            set_reg(regid1, it.result);
            name_to_reg.find(it.result)->second = regid1;
            fprintf(fp_asm, "LD [%d], R%d\n", symbol_table->find(it.arg1)->second.offset, regid1);
            fprintf(fp_asm, "MUL R%d, R%d, R%d\n", regid1, regid1, regid2);
        }
        else if (strcmp(it.op, "/") == 0) {
            if (regid1 == IN_MEM) {
                regid1 = getreg();
                set_reg(regid1, it.arg1);
                name_to_reg.find(it.arg1)->second = regid1;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid1, symbol_table->find(it.arg1)->second.offset);
            }
            if (regid2 == IN_MEM) {
                regid2 = getreg();
                set_reg(regid2, it.arg2);
                name_to_reg.find(it.arg2)->second = regid2;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid2, symbol_table->find(it.arg2)->second.offset);
            }
            if (regid1 == regid2) {
                printf("panic!\n");
                exit(-1);
            }
            if (name_to_reg.find(it.result)->second != IN_MEM) {
                free_reg(name_to_reg.find(it.result)->second);
            }
            name_to_reg.find(it.arg1)->second = IN_MEM;
            set_reg(regid1, it.result);
            name_to_reg.find(it.result)->second = regid1;
            fprintf(fp_asm, "LD [%d], R%d\n", symbol_table->find(it.arg1)->second.offset, regid1);
            fprintf(fp_asm, "DIV R%d, R%d, R%d\n", regid1, regid1, regid2);
        }
        else if (strcmp(it.op, "assign") == 0) {
            if (name_to_reg.find(it.result)->second != IN_MEM) {
                free_reg(name_to_reg.find(it.result)->second);
            }
            if (regid1 == IN_MEM) {
                regid1 = getreg();
                set_reg(regid1, it.result);
                name_to_reg.find(it.result)->second = regid1;
                fprintf(fp_asm, "LD R%d, [%d]\n", regid1, symbol_table->find(it.arg1)->second.offset);
            }
            else {
                if (name_to_reg.find(it.arg1) != name_to_reg.end()) {
                    name_to_reg.find(it.arg1)->second = IN_MEM;
                    fprintf(fp_asm, "LD [%d], R%d\n", symbol_table->find(it.arg1)->second.offset, regid1);
                }
                set_reg(regid1, it.result);
                name_to_reg.find(it.result)->second = regid1;
            }
        }
        else {
            printf("error! cannot generate asm code!\n");
            fprintf(fp_asm, "error! cannot generate asm code!\n");
        }
    }
    fclose(fp_asm);
}
