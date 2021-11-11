#include "lexer.h"

Lexer::Lexer(char *src) {
    offset = 0;
    init_sizeof_type();
    // 初始化编码表
    init_code_list();
    // 初始化关键字集合
    init_keywords_set();
    // 读取源代码
    read_src_file(src);
    // 分析获取token表
    init_token_list();
}

void Lexer::init_sizeof_type() {
    sizeof_type["int"] = sizeof(int);
    sizeof_type["float"] = sizeof(float);
    sizeof_type["bool"] = sizeof(bool);
    sizeof_type["char"] = sizeof(char);
    sizeof_type["long"] = sizeof(long);
    sizeof_type["double"] = sizeof(double);
}

void Lexer::init_code_list() {
    FILE *fp = fopen(CODE_LIST_FILEPATH, "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT "fail to open file: code_list.txt\n"RESET_STYLE);
        exit(0);
    }
    char ch;
    FlexBuffer flex_buf;
    while ((ch = fgetc(fp)) != EOF) {
        flex_buf.insert(ch);
    }
    fclose(fp);
    int cnt = 0;
    char *temp = flex_buf.get_line();
    while (temp != NULL) {
        cnt++;
        string str_temp = temp;
        code_list.insert(map<string, int>::value_type(str_temp, cnt));
        code_reverse.insert(map<int, string>::value_type(cnt, str_temp));
        free(temp);
        temp = flex_buf.get_line();
    }
    flex_buf.self_delete();
}

void Lexer::init_keywords_set() {
    FILE *fp = fopen(KEYWORD_SET_FILEPATH, "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT "fail to open file: keyword_set.txt\n"RESET_STYLE);
        exit(0);
    }
    char ch;
    FlexBuffer flex_buf;
    while ((ch = fgetc(fp)) != EOF) {
        flex_buf.insert(ch);
    }
    fclose(fp);
    int cnt = 0;
    char *temp = flex_buf.get_line();
    while (temp != NULL) {
        cnt++;
        string str_temp = temp;
        keywords_set.insert(str_temp);
        free(temp);
        temp = flex_buf.get_line();
    }
    flex_buf.self_delete();
}

void Lexer::init_token_list() {
    fbuf_forward = 0;
    fbuf_beginning = 0;
    token t = token_scan();
    while (t.typecode != TOKEN_EOF) {
        token_list.push_back(t);
        t = token_scan();
    }
}

// 装载源程序文件
void Lexer::read_src_file(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT "fail to open source file!\n"RESET_STYLE);
        exit(0);
    }
    char ch;
    FlexBuffer flex_buf;
    while ((ch = fgetc(fp)) != EOF) {
        flex_buf.insert(ch);
    }
    fclose(fp);
    fbuf_len = flex_buf.nextfree;
    fbuf = (char*)malloc(sizeof(char) * (fbuf_len));
    memcpy(fbuf, flex_buf.buf, sizeof(char) * fbuf_len);
    flex_buf.self_delete();
}

// 读一个字符
char Lexer::getch() {
    fbuf_forward++;
    return fbuf[fbuf_forward - 1];
}

// 判断是不是字母
bool Lexer::isalpha(char ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
        return true;
    }
    else if (ch == 95) {
        return true;
    }
    else {
        return false;
    }
}

// 判断是不是数字
bool Lexer::isdigit(char ch) {
    if (ch >= 48 && ch <= 57) {
        return true;
    }
    else {
        return false;
    }
}

// 判断是不是十六进制
bool Lexer::ishex(char ch) {
    if (isdigit(ch)) {
        return true;
    }
    else if (ch >= 65 && ch <= 70) {
        return true;
    }
    else if (ch >= 97 && ch <= 102) {
        return true;
    }
    else {
        return false;
    }
}

// 判断是不是八进制
bool Lexer::isoctal(char ch) {
    if (ch >= 48 && ch <= 55) {
        return true;
    }
    else {
        return false;
    }
}

// 判断是不是二进制
bool Lexer::isbinary(char ch) {
    if (ch == '0' || ch == '1') {
        return true;
    }
    else {
        return false;
    }
}

// 把截取的token复制出来
char* Lexer::copytoken() {
    int len = fbuf_forward - fbuf_beginning;
    char *tkn = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++) {
        tkn[i] = fbuf[fbuf_beginning + i];
    }
    tkn[len] = '\0';
    fbuf_beginning = fbuf_forward;
    return tkn;
}

// 判断是否为关键字
bool Lexer::iskeyword(char *tkn) {
    if (keywords_set.find(tkn) == keywords_set.end()) {
        return false;
    }
    else {
        return true;
    }
}

// 插入符号表
// 先判断是否已经存在
// 若存在则不插入
// 若不存在再插入
void Lexer::symboltable_insert(char *name) {
    if (symbol_table.find(name) == symbol_table.end()) {
        // 插入
        int len = strlen(name);
        symbol sym;
        sym.name = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++) {
            sym.name[i] = name[i];
        }
        sym.name[len] = '\0';
        sym.category = -1;
        sym.type = -1;
        sym.offset = -1;
        sym.attr = NULL;
        string sym_str = sym.name;
        symbol_table.insert(map<string, symbol>::value_type(sym_str, sym));
    }
}

// token 错误处理程序
token Lexer::error_handler() {
    char *tkn = copytoken();
    token res;
    res.typecode = TOKEN_ERROR;
    res.value = tkn;
    return res;
}

// 自动机获取token
token Lexer::token_scan() {
    char ch;
    char *tkn;
    int sym;
    token res;
    ch = getch();
    while (ch == ' ' || ch == 9 || ch == '\n' || ch == '\r') {
        ch = getch();
        fbuf_beginning++;
    }
    if (ch == '\0') {
        fbuf_forward--;
        res.typecode = TOKEN_EOF;
    }
    else if (isalpha(ch)) {
        ch = getch();
        while (isalpha(ch) || isdigit(ch)) {
            ch = getch();
        }
        fbuf_forward--;
        tkn = copytoken();
        if (iskeyword(tkn)) {
            // 如果是关键字
            res.typecode = code_list.find(tkn)->second;
            res.value = tkn;
        }
        else {
            // 如果不是关键字
            res.typecode = code_list.find("id")->second;
            res.value = tkn;
            // 插入符号表中去
            symboltable_insert(tkn);
        }
    }
    else if (isdigit(ch)) {
        if (ch == '0') {
            // 判断是否是其他进制
            ch = getch();
            if (ch == 'x' || ch == 'X') {
                // 16进制
                ch = getch();
                while (ishex(ch)) {
                    ch = getch();
                }
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("const_number_16")->second;
                res.value = tkn;
            }
            else if (ch == 'b' || ch == 'B') {
                // 2进制
                ch = getch();
                while (isbinary(ch)) {
                    ch = getch();
                }
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("const_number_2")->second;
                res.value = tkn;
            }
            else if (isoctal(ch)) {
                // 八进制
                ch = getch();
                while (isoctal(ch)) {
                    ch = getch();
                }
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("const_number_8")->second;
                res.value = tkn;
            }
            else {
                // 错误处理
                res = error_handler();
            }
        }
        else {
            // 否则是十进制
            ch = getch();
            while (isdigit(ch)) {
                ch = getch();
            }
            fbuf_forward--;
            tkn = copytoken();
            res.typecode = code_list.find("const_number")->second;
            res.value = tkn;
        }
    }
    else {
        switch(ch) {
        case '*': 
            ch = getch();
            if (ch == '*') {
                tkn = copytoken();
                res.typecode = code_list.find("**")->second;
                res.value = tkn;
            }
            else if (ch == '=') {
                tkn = copytoken();
                res.typecode = code_list.find("*=")->second;
                res.value = tkn;
            }
            else {
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("*")->second;
                res.value = tkn;
            }
            break;
        case '=': 
            ch = getch();
            if (ch == '=') {
                tkn = copytoken();
                res.typecode = code_list.find("==")->second;
                res.value = tkn;
            }
            else {
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("=")->second;
                res.value = tkn;
            }
            break;
        case '"': 
            ch = getch();
            while (ch != '"') {
                ch = getch();
            }
            tkn = copytoken();
            res.typecode = code_list.find("const_string")->second;
            res.value = tkn;
            break;
        case '(': 
            tkn = copytoken();
            res.typecode = code_list.find("(")->second;
            res.value = tkn;
            break;
        case ')': 
            tkn = copytoken();
            res.typecode = code_list.find(")")->second;
            res.value = tkn;
            break;
        case ':': 
            tkn = copytoken();
            res.typecode = code_list.find(":")->second;
            res.value = tkn;
            break;
        case '+': 
            ch = getch();
            if (ch == '+') {
                tkn = copytoken();
                res.typecode = code_list.find("++")->second;
                res.value = tkn;
            }
            else if (ch == '=') {
                tkn = copytoken();
                res.typecode = code_list.find("+=")->second;
                res.value = tkn;
            }
            else {
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("+")->second;
                res.value = tkn;
            }
            break;
        case '-': 
            ch = getch();
            if (ch == '-') {
                tkn = copytoken();
                res.typecode = code_list.find("--")->second;
                res.value = tkn;
            }
            else if (ch == '=') {
                tkn = copytoken();
                res.typecode = code_list.find("-=")->second;
                res.value = tkn;
            }
            else {
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("-")->second;
                res.value = tkn;
            }
            break;
        case '/': 
            ch = getch();
            if (ch == '=') {
                tkn = copytoken();
                res.typecode = code_list.find("/=")->second;
                res.value = tkn;
            }
            else {
                fbuf_forward--;
                tkn = copytoken();
                res.typecode = code_list.find("/")->second;
                res.value = tkn;
            }
            break;
        case ',': 
            tkn = copytoken();
            res.typecode = code_list.find(",")->second;
            res.value = tkn;
            break;
        case '{': 
            tkn = copytoken();
            res.typecode = code_list.find("{")->second;
            res.value = tkn;
            break;
        case '}': 
            tkn = copytoken();
            res.typecode = code_list.find("}")->second;
            res.value = tkn;
            break;
        case ';': 
            tkn = copytoken();
            res.typecode = code_list.find(";")->second;
            res.value = tkn;
            break;
        default:
            // 错误处理
            res = error_handler();
            break;
        }
    }
    return res;
}


void Lexer::output_files() {
    // 输出token文件
    printf("lexer: try to open token.txt\n");
    FILE *fp = fopen("token.txt", "w");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT"lexer: fail to open token.txt\n"RESET_STYLE);
        exit(0);
    }
    int i = 1;
    for (vector<token>::iterator ite = token_list.begin(); ite != token_list.end(); ite++) {
        fprintf(fp, "(%d,%s)\n", ite->typecode, ite->value);
        printf("lexer: it has already written [%d]\r", i);
        i++;
    }
    printf("\n");
    fclose(fp);
    printf("lexer: close token.txt\n");

    // 输出symbolTable.txt文件
    printf("lexer: try to open symbolTable.txt\n");
    fp = fopen("symbolTable.txt", "w");
    if (fp == NULL) {
        printf(FONT_RED FONT_HIGHLIGHT"lexer: fail to open symbol_table.txt\n"RESET_STYLE);
        exit(0);
    }
    i = 1;
    for (map<string, symbol>::iterator ite = symbol_table.begin(); ite != symbol_table.end(); ite++) {
        fprintf(fp, "(%s,%d,%d,%d,%d)\n", ite->second.name, ite->second.category, ite->second.type, ite->second.offset, ite->second.attr);
        printf("lexer: it has already written [%d]\r", i);
        i++;
    }
    printf("\n");
    fclose(fp);
    printf("lexer: close symbol_table.txt\n");
}
