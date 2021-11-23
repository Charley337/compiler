#include "assembly_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_const_int(char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (text[i] < '0' || text[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// assign
void assembly_function_0(Assembly* assm, ILitem it) {
    if (is_const_int(it.arg1)) {
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
        }
    }
    else {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
        }
    }
}

// +
void assembly_function_1(Assembly* assm, ILitem it) {
    if (is_const_int(it.arg1) && is_const_int(it.arg2)) {
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2));
        }
    }
    else if (is_const_int(it.arg1)) {
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg1));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg1));
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid2, atoi(it.arg1));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid2, atoi(it.arg1));
        }
    }
    else if (is_const_int(it.arg2)) {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2));
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid1, atoi(it.arg2));
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid1, atoi(it.arg2));
        }
    }
    else {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regid2 == IN_MEM) {
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid1);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid1);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
        else if (regid2 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid1);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "add x%d, x%d, x%d\n", regidres, regid1, regid2);
        }
    }
}

// -
void assembly_function_2(Assembly* assm, ILitem it) {
    if (is_const_int(it.arg1) && is_const_int(it.arg2)) {
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1) * -1);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2) * -1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1) * -1);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2) * -1);
        }
    }
    else if (is_const_int(it.arg1)) {
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            regid2 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid2, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
            assm->name_to_reg.find(it.arg2)->second = regid2;
            assm->set_reg(regid2, it.arg2);
        }
        else if (regid2 == IN_MEM) {
            regid2 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid2, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.arg2)->second = regid2;
            assm->set_reg(regid2, it.arg2);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid2, atoi(it.arg1) * -1);
            fprintf(assm->fp_asm, "sub x%d, x0, x%d\n", regidres, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid2, atoi(it.arg1) * -1);
            fprintf(assm->fp_asm, "sub x%d, x0, x%d\n", regidres, regidres);
        }
    }
    else if (is_const_int(it.arg2)) {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2) * -1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regidres, atoi(it.arg2) * -1);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid1, atoi(it.arg2) * -1);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x%d, %d\n", regidres, regid1, atoi(it.arg2) * -1);
        }
    }
    else {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regid2 == IN_MEM) {
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid1);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
        else if (regid2 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regid1, regidres);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "sub x%d, x%d, x%d\n", regidres, regid1, regid2);
        }
    }
}

// *
void assembly_function_3(Assembly* assm, ILitem it) {
    if (is_const_int(it.arg1) && is_const_int(it.arg2)) {
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regidtemp);
        }
    }
    else if (is_const_int(it.arg1)) {
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidtemp, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM) {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidtemp, regidres);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid2);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidtemp, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
    }
    else if (is_const_int(it.arg2)) {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regidtemp);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg2));
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regidres);
        }
    }
    else {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regid2 == IN_MEM) {
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid1);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
        else if (regid2 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regidres);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "mul x%d, x%d, x%d\n", regidres, regid1, regid2);
        }
    }
}

// /
void assembly_function_4(Assembly* assm, ILitem it) {
    if (is_const_int(it.arg1) && is_const_int(it.arg2)) {
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regidtemp);
        }
    }
    else if (is_const_int(it.arg1)) {
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidtemp, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM) {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidtemp, regidres);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid2);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg1));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidtemp, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg1));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
    }
    else if (is_const_int(it.arg2)) {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regidtemp);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg();
            int regidtemp = assm->getreg(regidres);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidtemp, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regidtemp);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "addi x%d, x0, %d\n", regidres, atoi(it.arg2));
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regidres);
        }
    }
    else {
        int regid1 = assm->name_to_reg.find(it.arg1)->second;
        int regid2 = assm->name_to_reg.find(it.arg2)->second;
        int regidres = assm->name_to_reg.find(it.result)->second;
        if (regid1 == IN_MEM && regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg();
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regid2 == IN_MEM) {
            regid1 = assm->getreg(regidres);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regid1, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.arg1)->second = regid1;
            assm->set_reg(regid1, it.arg1);
        }
        else if (regid1 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid2 == IN_MEM && regidres == IN_MEM) {
            regidres = assm->getreg(regid1);
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regidres);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else if (regid1 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg1)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regid2);
        }
        else if (regid2 == IN_MEM) {
            fprintf(assm->fp_asm, "lw x%d, %d(x0)\n", regidres, assm->symbol_table->find(it.arg2)->second.offset);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regidres);
        }
        else if (regidres == IN_MEM) {
            regidres = assm->getreg(regid2);
            fprintf(assm->fp_asm, "add x%d, x0, x%d\n", regidres, regid1);
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regidres, regid2);
            assm->name_to_reg.find(it.result)->second = regidres;
            assm->set_reg(regidres, it.result);
        }
        else {
            fprintf(assm->fp_asm, "div x%d, x%d, x%d\n", regidres, regid1, regid2);
        }
    }
}
