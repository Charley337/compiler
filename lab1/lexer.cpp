#include "lexer.h"

Lexer::Lexer(char *src) {
    // 初始化编码表
    init_code_list();
    // 初始化关键字集合
    init_keywords_set();
    // 读取源代码
    read_src_file(src);
    // 分析获取token表
    init_token_list();
}

void Lexer::init_code_list() {
    code_list.insert(map<string, int>::value_type("id", 1));
    code_list.insert(map<string, int>::value_type("const_number", 2));
    code_list.insert(map<string, int>::value_type("true", 3));
    code_list.insert(map<string, int>::value_type("const_string", 4));
    code_list.insert(map<string, int>::value_type("unsigned", 5));
    code_list.insert(map<string, int>::value_type("short", 6));
    code_list.insert(map<string, int>::value_type("int", 7));
    code_list.insert(map<string, int>::value_type("long", 8));
    code_list.insert(map<string, int>::value_type("float", 9));
    code_list.insert(map<string, int>::value_type("double", 10));
    code_list.insert(map<string, int>::value_type("char", 11));
    code_list.insert(map<string, int>::value_type("bool", 12));
    code_list.insert(map<string, int>::value_type("void", 13));
    code_list.insert(map<string, int>::value_type("if", 14));
    code_list.insert(map<string, int>::value_type("else", 15));
    code_list.insert(map<string, int>::value_type("while", 16));
    code_list.insert(map<string, int>::value_type("do", 17));
    code_list.insert(map<string, int>::value_type("for", 18));
    code_list.insert(map<string, int>::value_type("switch", 19));
    code_list.insert(map<string, int>::value_type("case", 20));
    code_list.insert(map<string, int>::value_type("break", 21));
    code_list.insert(map<string, int>::value_type("continue", 22));
    code_list.insert(map<string, int>::value_type("default", 23));
    code_list.insert(map<string, int>::value_type("struct", 24));
    code_list.insert(map<string, int>::value_type("static", 25));
    code_list.insert(map<string, int>::value_type("sizeof", 26));
    code_list.insert(map<string, int>::value_type("return", 27));
    code_list.insert(map<string, int>::value_type("volatile", 28));
    code_list.insert(map<string, int>::value_type("enum", 29));
    code_list.insert(map<string, int>::value_type("false", 30));
    code_list.insert(map<string, int>::value_type("=", 31));
    code_list.insert(map<string, int>::value_type(">", 32));
    code_list.insert(map<string, int>::value_type("<", 33));
    code_list.insert(map<string, int>::value_type("?", 34));
    code_list.insert(map<string, int>::value_type("==", 35));
    code_list.insert(map<string, int>::value_type("!=", 36));
    code_list.insert(map<string, int>::value_type(">=", 37));
    code_list.insert(map<string, int>::value_type("<=", 38));
    code_list.insert(map<string, int>::value_type("+", 39));
    code_list.insert(map<string, int>::value_type("-", 40));
    code_list.insert(map<string, int>::value_type("*", 41));
    code_list.insert(map<string, int>::value_type("/", 42));
    code_list.insert(map<string, int>::value_type("%", 43));
    code_list.insert(map<string, int>::value_type("^", 44));
    code_list.insert(map<string, int>::value_type("++", 45));
    code_list.insert(map<string, int>::value_type("+=", 46));
    code_list.insert(map<string, int>::value_type("-=", 47));
    code_list.insert(map<string, int>::value_type("*=", 48));
    code_list.insert(map<string, int>::value_type("/=", 49));
    code_list.insert(map<string, int>::value_type("**", 50));
    code_list.insert(map<string, int>::value_type("!", 51));
    code_list.insert(map<string, int>::value_type("&", 52));
    code_list.insert(map<string, int>::value_type("|", 53));
    code_list.insert(map<string, int>::value_type("&&", 54));
    code_list.insert(map<string, int>::value_type("||", 55));
    code_list.insert(map<string, int>::value_type("->", 56));
    code_list.insert(map<string, int>::value_type(".", 57));
    code_list.insert(map<string, int>::value_type(",", 58));
    code_list.insert(map<string, int>::value_type(":", 59));
    code_list.insert(map<string, int>::value_type(";", 60));
    code_list.insert(map<string, int>::value_type("(", 61));
    code_list.insert(map<string, int>::value_type(")", 62));
    code_list.insert(map<string, int>::value_type("[", 63));
    code_list.insert(map<string, int>::value_type("]", 64));
    code_list.insert(map<string, int>::value_type("{", 65));
    code_list.insert(map<string, int>::value_type("}", 66));
    code_list.insert(map<string, int>::value_type("--", 67));
    code_list.insert(map<string, int>::value_type("include", 68));
    code_list.insert(map<string, int>::value_type("#", 69));
    code_list.insert(map<string, int>::value_type("define", 70));
    code_list.insert(map<string, int>::value_type("typedef", 71));
    code_list.insert(map<string, int>::value_type("const_number_2", 72));
    code_list.insert(map<string, int>::value_type("const_number_8", 73));
    code_list.insert(map<string, int>::value_type("const_number_16", 74));
}

void Lexer::init_keywords_set() {
    keywords_set.insert("unsigned");
    keywords_set.insert("short");
    keywords_set.insert("int");
    keywords_set.insert("long");
    keywords_set.insert("float");
    keywords_set.insert("double");
    keywords_set.insert("char");
    keywords_set.insert("bool");
    keywords_set.insert("void");
    keywords_set.insert("if");
    keywords_set.insert("else");
    keywords_set.insert("while");
    keywords_set.insert("do");
    keywords_set.insert("for");
    keywords_set.insert("switch");
    keywords_set.insert("case");
    keywords_set.insert("break");
    keywords_set.insert("continue");
    keywords_set.insert("default");
    keywords_set.insert("struct");
    keywords_set.insert("static");
    keywords_set.insert("sizeof");
    keywords_set.insert("return");
    keywords_set.insert("volatile");
    keywords_set.insert("enum");
    keywords_set.insert("true");
    keywords_set.insert("false");
    keywords_set.insert("include");
    keywords_set.insert("define");
    keywords_set.insert("typedef");
}

void Lexer::init_token_list() {
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
    fseek(fp, 0, SEEK_END);
    fbuf_len = ftell(fp);
    rewind(fp);
    fbuf = (char*)malloc(sizeof(char) * (fbuf_len + 1));
    fread(fbuf, fbuf_len, 1, fp);
    fclose(fp);
    fbuf_beginning = 0;
    fbuf_forward = 0;
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
        sym.type = code_list.find("id")->second;
        sym.offset = 0;
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
        fprintf(fp, "(%s,-1,?)\n", ite->second.name);
        printf("lexer: it has already written [%d]\r", i);
        i++;
    }
    printf("\n");
    fclose(fp);
    printf("lexer: close symbol_table.txt\n");
}
