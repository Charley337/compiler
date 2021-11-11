#include "lr1_analyser.h"
#include "translate_proc.h"

LR1Analyser::LR1Analyser(Lexer *le) {
    lex = le;
    token_it = lex->token_list.begin();
    proc_list_init();
    grammar_list_init();
    at_init();
    stack_init();
}

void LR1Analyser::proc_list_init() {
    void (*buf[])(SymNode*, SymList*, Lexer*) = {
        NULL,
        proc_grammar_1,
        proc_grammar_2,
        proc_grammar_3,
        proc_grammar_4,
        proc_grammar_5,
        proc_grammar_6,
        proc_grammar_7,
        proc_grammar_8,
        proc_grammar_9,
        proc_grammar_10,
        proc_grammar_11,
        proc_grammar_12,
        proc_grammar_13,
        proc_grammar_14,
        proc_grammar_15,
        proc_grammar_16,
        proc_grammar_17,
        proc_grammar_18,
        proc_grammar_19,
        proc_grammar_20,
        proc_grammar_21,
        proc_grammar_22,
        NULL,
    };
    proc_num = 1;
    while (buf[proc_num] != NULL) {
        proc_num++;
    }
    proc_num--;
    proc_list = (void (**)(SymNode*, SymList*, Lexer*))malloc(sizeof(void (*)(SymNode*, SymList*, Lexer*)) * (proc_num + 1));
    for (int i = 0; i <= proc_num; i++) {
        proc_list[i] = buf[i];
    }
}


// 栈初始化
void LR1Analyser::stack_init() {
    // 先清空
    while (!state_stack.empty()) {
        state_stack.pop();
    }
    while (!symbol_stack.empty()) {
        symbol_stack.pop();
    }
    // 初始化
    state_stack.push(0);
    SymNode temp;
    temp.id = lex->code_list.find("#")->second;
    temp.attr = NULL;
    symbol_stack.push(temp);
}


// 读一行
int LR1Analyser::get_line(char *line, char *buffer, int *bp) {
    int begin = *bp;
    while (buffer[*bp] != '\0' && buffer[*bp] != '\n') {
        (*bp)++;
    }
    if (buffer[*bp] == '\0' && (*bp) == begin) {
        return 0;
    }
    else if (buffer[*bp] == '\0' && (*bp) != begin) {
        for (int i = 0; i < ((*bp) - begin); i++) {
            line[i] = buffer[begin + i];
        }
        line[(*bp) - begin] = '\0';
        return 1;
    }
    else {
        for (int i = 0; i < ((*bp) - begin); i++) {
            line[i] = buffer[begin + i];
        }
        line[(*bp) - begin] = '\0';
        (*bp)++;
        return 1;
    }
}


int LR1Analyser::get_value(char *val, char *line, int *lp) {
    int begin = *lp;
    while (line[*lp] != '\0' && line[*lp] != ',') {
        if (line[*lp] == '"') {
            (*lp)++;
            while (line[*lp] != '"') {
                (*lp)++;
                if (line[*lp] == '\0') {
                    printf("lr1 get_value error\n");
                    exit(0);
                }
            }
        }
        (*lp)++;
    }
    if (line[*lp] == '\0' && (*lp) == begin) {
        return 0;
    }
    else if (line[*lp] == '\0' && (*lp) != begin) {
        for (int i = 0; i < ((*lp) - begin); i++) {
            val[i] = line[begin + i];
        }
        val[(*lp) - begin] = '\0';
        return 1;
    }
    else {
        for (int i = 0; i < ((*lp) - begin); i++) {
            val[i] = line[begin + i];
        }
        val[(*lp) - begin] = '\0';
        (*lp)++;
        if (val[0] == '"') {
            for (int j = 0; j < strlen(val); j++) {
                val[j] = val[j + 1];
            }
            val[strlen(val) - 1] = '\0';
            // printf("%s\n", val);
        }
        return 1;
    }
}


int LR1Analyser::get_digit_from_value(char *val) {
    int len = strlen(val);
    int res = 0;
    if (val[0] == 'a') {
        return 0;
    }
    else if (val[0] == 's') {
        for (int i = 6; i < len; i++) {
            res *= 10;
            res += val[i] - 48;
        }
    }
    else if (val[0] == 'r') {
        if (grammar_reverse.find(val + 7) == grammar_reverse.end()) {
            printf("cannot find grammar\n");
            exit(0);
        }
        res = grammar_reverse.find(val + 7)->second;
    }
    else {
        for (int i = 0; i < len; i++) {
            res *= 10;
            res += val[i] - 48;
        }
    }
    return res;
}


// 分析表初始化
void LR1Analyser::at_init() {
    FILE *fp = fopen("LR1.csv", "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT "fail to open LR1.csv\n"RESET_STYLE);
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    char *buffer = (char*)malloc(sizeof(char) * (len + 1));
    fread(buffer, len, 1, fp);
    char *line = (char*)malloc(sizeof(char) * (len + 1));
    char *val = (char*)malloc(sizeof(char) * (len + 1));
    int bp = 0;
    int lp = 0;
    fclose(fp);

    int row = 0;
    int col = 0;
    int max_col = 0;
    char *val_temp;
    get_line(line, buffer, &bp);
    while (get_line(line, buffer, &bp)) {
        col = 0;
        lp = 0;
        while (get_value(val, line, &lp)) {
            RowCol row_col;
            row_col.row = row;
            row_col.col = col;
            len = strlen(val);
            val_temp = (char*)malloc(sizeof(char) * (len + 1));
            for (int i = 0; i < len; i++) {
                val_temp[i] = val[i];
            }
            val_temp[len] = '\0';
            lr1_table.insert(map<RowCol, char*>::value_type(row_col, val_temp));
            col++;
        }
        if (row == 0) {
            max_col = col;
        }
        row++;
    }

    RowCol temp_rc;
    ATindex temp_ati;
    ATval temp_atv;
    map<RowCol, char*>::iterator temp_ite;
    int divider;
    // 寻找分界符 $
    temp_rc.row = 0;
    for (int i = 0; i < max_col; i++) {
        temp_rc.col = i;
        temp_ite = lr1_table.find(temp_rc);
        if (temp_ite != lr1_table.end() && strlen(temp_ite->second) != 0) {
            if (strcmp(temp_ite->second, "$") == 0) {
                divider = i;
                break;
            }
        }
    }
    // 插入 analyse_table 中去
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < max_col; j++) {
            temp_rc.row = i;
            temp_rc.col = j;
            temp_ite = lr1_table.find(temp_rc);
            if (temp_ite != lr1_table.end() && strlen(temp_ite->second) != 0) {
                temp_ati.state = i - 1;
                temp_ati.table = (j <= divider) ? AT_TABLE_ACTION : AT_TABLE_GOTO;
                temp_rc.row = 0;
                temp_rc.col = j;
                if (lex->code_list.find(lr1_table.find(temp_rc)->second) == lex->code_list.end()) {
                    printf("code_list cannot find! (%d, %d): %s\n", temp_rc.row, temp_rc.col, lr1_table.find(temp_rc)->second);
                    exit(0);
                }
                temp_ati.symbol = lex->code_list.find(lr1_table.find(temp_rc)->second)->second;
                if (temp_ite->second[0] == 's') {
                    temp_atv.type = AT_TYPE_SHIFT;
                }
                else if (temp_ite->second[0] == 'r') {
                    temp_atv.type = AT_TYPE_REDUCE;
                }
                else if (temp_ite->second[0] == 'a') {
                    temp_atv.type = AT_TYPE_ACC;
                }
                else {
                    temp_atv.type = AT_TYPE_GOTO;
                }
                temp_atv.val = get_digit_from_value(temp_ite->second);
                analyse_table.insert(map<ATindex, ATval>::value_type(temp_ati, temp_atv));
            }
        }
    }

    free(buffer);
    free(line);
    free(val);
}


void LR1Analyser::grammar_list_init() {
    FILE *fp = fopen("wenfa.txt", "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT "fail to open wenfa.txt\n"RESET_STYLE);
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    char *buffer = (char*)malloc(sizeof(char) * (len + 1));
    fread(buffer, len, 1, fp);
    char *line = (char*)malloc(sizeof(char) * (len + 1));
    int bp = 0;
    fclose(fp);

    // 求出共有多少行
    int num_line = 0;
    while (get_line(line, buffer, &bp)) {
        num_line++;
    }
    grammar_list_len = num_line;

    // 获取文法
    bp = 0;
    int i = 1;
    grammar_list = (char**)malloc(sizeof(char*) * (num_line + 2));
    while (get_line(line, buffer, &bp)) {
        len = strlen(line);
        grammar_list[i] = (char*)malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len; j++) {
            grammar_list[i][j] = line[j];
        }
        grammar_list[i][len] = '\0';
        i++;
    }
    free(buffer);
    free(line);

    // 初始化文法查找表
    for (int i = 1; i <= grammar_list_len; i++) {
        grammar_reverse.insert(map<string, int>::value_type(grammar_list[i], i));
    }
}

void LR1Analyser::lr1_start() {
    // always action, until accept
    while (token_it != lex->token_list.end()) {
        // printf("(%d, %s)\n", token_it->typecode, token_it->value);
        shift_action();
        token_it++;
    }
    printf(FONT_GREEN"lr1 grammar analyse pass!\n"RESET_STYLE);
}

void LR1Analyser::shift_action() {
    int sym = token_it->typecode;
    if (sym == lex->code_list.find(";")->second) {
        sym = lex->code_list.find("$")->second;
    }
    ATindex idx;
    idx.table = AT_TABLE_ACTION;
    idx.state = state_stack.top();
    idx.symbol = sym;
    map<ATindex, ATval>::iterator it = analyse_table.find(idx);
    if (it != analyse_table.end()) {
        int type = it->second.type;
        int val = it->second.val;
        if (type == AT_TYPE_SHIFT) {        // 如果是shift，那么把新的状态值（val）和符号（sym）读取到栈中。
            state_stack.push(val);
            SymNode symnodetemp;
            symnodetemp.id = sym;
            symnodetemp.attr = (Attr*)malloc(sizeof(Attr));
            symnodetemp.attr->attr_name = "name";
            symnodetemp.attr->val = (char*)malloc(sizeof(char) * (strlen(token_it->value) + 1));
            strcpy((char*)symnodetemp.attr->val, token_it->value);
            symnodetemp.attr->next = NULL;
            symbol_stack.push(symnodetemp);
        }
        else if (type == AT_TYPE_REDUCE) {      // 如果是reduce，那么归约
            reduce(val);
        }
        else if (type == AT_TYPE_ACC) {
            accept();
            stack_init();
        }
        else {
            printf("error happen! type = %d\n", type);
            printf("(%d, %d, %d): (%d, %d)\n", it->first.table, it->first.state, it->first.symbol, it->second.type, it->second.val);
            exit(0);
        }
    }
    else {
        printf("analyse_table action cannot find!\n");
        exit(0);
    }
}

void LR1Analyser::shift_goto() {
    ATindex idx;
    idx.table = AT_TABLE_GOTO;
    idx.state = state_stack.top();
    idx.symbol = symbol_stack.top().id;
    map<ATindex, ATval>::iterator it = analyse_table.find(idx);
    if (it != analyse_table.end()) {
        int type = it->second.type;
        int val = it->second.val;
        if (type == AT_TYPE_GOTO) {
            state_stack.push(val);
            shift_action();
        }
        else {
            printf("error happen! goto type\n");
            exit(0);
        }
    }
    else {
        printf("analyse_table goto cannot find!\n");
        exit(0);
    }
}

void LR1Analyser::reduce(int val) {
    char *gram = grammar_list[val];
    printf("%s\n", gram);
    // 从后往前，直到箭头
    int pf = strlen(gram);
    int pb = strlen(gram);
    char *tk;
    SymList *symhead = NULL;
    SymNode symfather;
    while (gram[pf] != '>') {
        if (gram[pf] == ' ') {
            while (gram[pf] == ' ') {
                pf--;
            }
            pb = pf;
            // 符号串
            SymList *symlist_temp = (SymList*)malloc(sizeof(SymList));
            symlist_temp->sym = symbol_stack.top();
            symlist_temp->next = symhead;
            symhead = symlist_temp;
            state_stack.pop();
            symbol_stack.pop();
            continue;
        }
        pf--;
    }
    pf = 0;
    while (gram[pf] != ' ') {
        pf++;
    }
    tk = (char*)malloc(sizeof(char) * (pf + 1));
    memcpy(tk, gram, sizeof(char) * (pf));
    tk[pf] = '\0';
    symfather.id = lex->code_list.find(tk)->second;
    symfather.attr = NULL;
    proc_list[val](&symfather, symhead, lex);
    symbol_stack.push(symfather);
    // always goto after reduce
    shift_goto();
}

void LR1Analyser::accept() {
    printf(FONT_GREEN "Accept a sentence.\n"RESET_STYLE);
}

void LR1Analyser::error_handle() {

}

