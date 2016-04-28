//
//  lexer.cpp
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "lexer.h"

/* 初始化词法分析器里面的静态变量 */
int Lexer::LEXER_ERROR = 0;
int Lexer::lineNumber = 1;
int Lexer::linePos = 0;
std::string Lexer::tokenString = "";

/* 实现构造函数 */
Lexer::Lexer(std::string fileName) {
    
    scanListing = stdout;
    
    /** 
     * 初始化关键字
     * 关键字: 0x103
     */
    keyWords.clear();
    keyWords.insert(std::make_pair("abstract", std::make_pair(ABSTRACT, "0x103")));
    keyWords.insert(std::make_pair("boolean", std::make_pair(BOOLEAN, "0x103")));
    keyWords.insert(std::make_pair("break", std::make_pair(BREAK, "0x103")));
    keyWords.insert(std::make_pair("byte", std::make_pair(BYTE, "0x103")));
    keyWords.insert(std::make_pair("case", std::make_pair(CASE, "0x103")));
    keyWords.insert(std::make_pair("catch", std::make_pair(CATCH, "0x103")));
    keyWords.insert(std::make_pair("char", std::make_pair(CHAR, "0x103")));
    keyWords.insert(std::make_pair("class", std::make_pair(CLASS, "0x103")));
    keyWords.insert(std::make_pair("const", std::make_pair(CONST, "0x103")));
    keyWords.insert(std::make_pair("continue", std::make_pair(CONTINUE, "0x103")));
    keyWords.insert(std::make_pair("default", std::make_pair(DEFAULT, "0x103")));
    keyWords.insert(std::make_pair("do", std::make_pair(DO, "0x103")));
    keyWords.insert(std::make_pair("double", std::make_pair(DOUBLE, "0x103")));
    keyWords.insert(std::make_pair("else", std::make_pair(ELSE, "0x103")));
    keyWords.insert(std::make_pair("extends", std::make_pair(EXTENDS, "0x103")));
    keyWords.insert(std::make_pair("false", std::make_pair(JAVA_FALSE, "0x103")));
    keyWords.insert(std::make_pair("final", std::make_pair(FINAL, "0x103")));
    keyWords.insert(std::make_pair("finally", std::make_pair(FINALLY, "0x103")));
    keyWords.insert(std::make_pair("float", std::make_pair(FLOAT, "0x103")));
    keyWords.insert(std::make_pair("for", std::make_pair(FOR, "0x103")));
    keyWords.insert(std::make_pair("goto", std::make_pair(GOTO, "0x103")));
    keyWords.insert(std::make_pair("if", std::make_pair(IF, "0x103")));
    keyWords.insert(std::make_pair("implements", std::make_pair(IMPLEMENTES, "0x103")));
    keyWords.insert(std::make_pair("import", std::make_pair(IMPORT, "0x103")));
    keyWords.insert(std::make_pair("instanceof", std::make_pair(INSTANCEOF, "0x103")));
    keyWords.insert(std::make_pair("int", std::make_pair(INT, "0x103")));
    keyWords.insert(std::make_pair("interface", std::make_pair(INTERFACE, "0x103")));
    keyWords.insert(std::make_pair("long", std::make_pair(LONG, "0x103")));
    keyWords.insert(std::make_pair("native", std::make_pair(NATIVE, "0x103")));
    keyWords.insert(std::make_pair("new", std::make_pair(NEW, "0x103")));
    keyWords.insert(std::make_pair("null", std::make_pair(JAVA_NULL, "0x103")));
    keyWords.insert(std::make_pair("package", std::make_pair(PACKAGE, "0x103")));
    keyWords.insert(std::make_pair("private", std::make_pair(PRIVATE, "0x103")));
    keyWords.insert(std::make_pair("protected", std::make_pair(PROTECTED, "0x103")));
    keyWords.insert(std::make_pair("public", std::make_pair(PUBLIC, "0x103")));
    keyWords.insert(std::make_pair("return", std::make_pair(RETURN, "0x103")));
    keyWords.insert(std::make_pair("short", std::make_pair(SHORT, "0x103")));
    keyWords.insert(std::make_pair("static", std::make_pair(STATIC, "0x103")));
    keyWords.insert(std::make_pair("super", std::make_pair(SUPER, "0x103")));
    keyWords.insert(std::make_pair("switch", std::make_pair(SWITCH, "0x103")));
    keyWords.insert(std::make_pair("synchronized", std::make_pair(SYNCHRONIZED, "0x103")));
    keyWords.insert(std::make_pair("this", std::make_pair(THIS, "0x103")));
    keyWords.insert(std::make_pair("throw", std::make_pair(THROW, "0x103")));
    keyWords.insert(std::make_pair("throws", std::make_pair(THROWS, "0x103")));
    keyWords.insert(std::make_pair("transient", std::make_pair(TRANSIENT, "0x103")));
    keyWords.insert(std::make_pair("true", std::make_pair(JAVA_TRUE, "0x103")));
    keyWords.insert(std::make_pair("try", std::make_pair(TRY, "0x103")));
    keyWords.insert(std::make_pair("void", std::make_pair(VOID, "0x103")));
    keyWords.insert(std::make_pair("volatile", std::make_pair(VOLATILE, "0x103")));
    keyWords.insert(std::make_pair("while", std::make_pair(WHILE, "0x103")));
    
    /**
     * 初始化tokenMap
     */
    tokenMap.clear();
    tokenMap.insert(std::make_pair(ENDFILE, std::make_pair("end of file", "0x000")));
    
    /**
     * 错误的单词: 0x100
     * 注释:      0x101
     * 空格:      0x102
     */
    tokenMap.insert(std::make_pair(TOKEN_ERROR, std::make_pair("token error", "0x100")));
    tokenMap.insert(std::make_pair(COMMENT, std::make_pair("comment", "0x101")));
    tokenMap.insert(std::make_pair(SPACE, std::make_pair("white space", "0x102")));
    
    /**
     * 标志符: 0x104
     * 布尔型: 0x105
     * 字符型: 0x106
     * 整型:   0x107
     * 浮点型: 0x108
     * 字符串: 0x109
     */
    tokenMap.insert(std::make_pair(ID, std::make_pair("identifier", "0x104")));
    tokenMap.insert(std::make_pair(CONST_BOOL, std::make_pair("bool const", "0x105")));
    tokenMap.insert(std::make_pair(CONST_CHAR, std::make_pair("char const", "0x106")));
    tokenMap.insert(std::make_pair(CONST_INT, std::make_pair("int const", "0x107")));
    tokenMap.insert(std::make_pair(CONST_FLOAT, std::make_pair("float const", "0x108")));
    tokenMap.insert(std::make_pair(CONST_STR, std::make_pair("string const", "0x109")));
    
    /**
     * 赋值运算符号: 0x110
     * = += -= *= /= %= &=
     * ^= |= >>= <<= >>>=
     */
    tokenMap.insert(std::make_pair(ASSIGN, std::make_pair("=", "0x110")));
    tokenMap.insert(std::make_pair(ADD_ASSIGN, std::make_pair("+=", "0x110")));
    tokenMap.insert(std::make_pair(MINUS_ASSIGN, std::make_pair("-=", "0x110")));
    tokenMap.insert(std::make_pair(MUL_ASSIGN, std::make_pair("*=", "0x110")));
    tokenMap.insert(std::make_pair(DIV_ASSIGN, std::make_pair("/=", "0x110")));
    tokenMap.insert(std::make_pair(MOD_ASSIGN, std::make_pair("%=", "0x110")));
    tokenMap.insert(std::make_pair(AND_ASSIGN, std::make_pair("&=", "0x110")));
    tokenMap.insert(std::make_pair(XOR_ASSIGN, std::make_pair("^=", "0x110")));
    tokenMap.insert(std::make_pair(OR_ASSIGN, std::make_pair("|=", "0x110")));
    tokenMap.insert(std::make_pair(RIGHT_SHIFT_ASSIGN, std::make_pair(">>=", "0x110")));
    tokenMap.insert(std::make_pair(LEFT_SHIFT_ASSIGN, std::make_pair("<<=", "0x110")));
    tokenMap.insert(std::make_pair(ZERO_FILL_RIGHT_SHIRT_ASSIGN, std::make_pair(">>>=", "0x110")));
    
    /**
     * 关系运算符号
     * ?:   0x111
     * ||:  0x112
     * &&:  0x113
     * | :  0x114
     * ^ :  0x115
     * & :  0x116
     */
    tokenMap.insert(std::make_pair(TRIPLE_CMP, std::make_pair("?:", "0x111")));
    tokenMap.insert(std::make_pair(OR, std::make_pair("||", "0x112")));
    tokenMap.insert(std::make_pair(AND, std::make_pair("&&", "0x113")));
    tokenMap.insert(std::make_pair(OR_BIT, std::make_pair("|", "0x114")));
    tokenMap.insert(std::make_pair(XOR, std::make_pair("^", "0x115")));
    tokenMap.insert(std::make_pair(AND_BIT, std::make_pair("&", "0x116")));
    
    /**
     * 比较运算符|移位运算符
     * == !=        : 0x117
     * < > <= >=    : 0x118
     * << >> >>>    : 0x119
     */
    tokenMap.insert(std::make_pair(EQU, std::make_pair("==", "0x117")));
    tokenMap.insert(std::make_pair(NE, std::make_pair("!=", "0x117")));
    tokenMap.insert(std::make_pair(LT, std::make_pair("<", "0x118")));
    tokenMap.insert(std::make_pair(GT, std::make_pair(">", "0x118")));
    tokenMap.insert(std::make_pair(LE, std::make_pair("<=", "0x118")));
    tokenMap.insert(std::make_pair(GE, std::make_pair(">=", "0x118")));
    tokenMap.insert(std::make_pair(LEFT_SHIFT, std::make_pair("<<", "0x119")));
    tokenMap.insert(std::make_pair(RIGHT_SHIFT, std::make_pair(">>", "0x119")));
    tokenMap.insert(std::make_pair(ZERO_FILL_RIGHT_SHIRT, std::make_pair(">>>", "0x119")));
    
    /**
     * 数值计算符号
     * + -                      : 0x11a
     * * / %                    : 0x11b
     * ++ -- +(正) –(负) ! ~     : 0x11c
     */
    tokenMap.insert(std::make_pair(ADD, std::make_pair("+", "0x11a")));
    tokenMap.insert(std::make_pair(MINUS, std::make_pair("-", "0x11a")));
    tokenMap.insert(std::make_pair(MUL, std::make_pair("*", "0x11b")));
    tokenMap.insert(std::make_pair(DIV, std::make_pair("/", "0x11b")));
    tokenMap.insert(std::make_pair(MOD, std::make_pair("%", "0x11b")));
    tokenMap.insert(std::make_pair(INC, std::make_pair("++", "0x11c")));
    tokenMap.insert(std::make_pair(DEC, std::make_pair("--", "0x11c")));
    tokenMap.insert(std::make_pair(POSITIVE, std::make_pair("+", "0x11c")));
    tokenMap.insert(std::make_pair(NEGATIVE, std::make_pair("-", "0x11c")));
    tokenMap.insert(std::make_pair(NOT, std::make_pair("!", "0x11c")));
    tokenMap.insert(std::make_pair(NOT_BIT, std::make_pair("~", "0x11c")));
    
    /**
     * 界限符
     * [] () .                  : 0x11d
     * ,                        : 0x120
     * {}                       : 0x121
     * ;                        : 0x122
     */
    tokenMap.insert(std::make_pair(BRACKET_ML, std::make_pair("[", "0x11d")));
    tokenMap.insert(std::make_pair(BRACKET_MR, std::make_pair("]", "0x11d")));
    tokenMap.insert(std::make_pair(BRACKET_SL, std::make_pair("(", "0x11d")));
    tokenMap.insert(std::make_pair(BRACKET_SR, std::make_pair(")", "0x11d")));
    tokenMap.insert(std::make_pair(DOT, std::make_pair(".", "0x11d")));
    tokenMap.insert(std::make_pair(COMMA, std::make_pair(",", "0x120")));
    tokenMap.insert(std::make_pair(BRACKET_LL, std::make_pair("{", "0x121")));
    tokenMap.insert(std::make_pair(BRACKET_LR, std::make_pair("}", "0x121")));
    tokenMap.insert(std::make_pair(SEMICOLON, std::make_pair(";", "0x122")));
    
    delimeterMap.clear();
    delimeterMap.insert(std::make_pair('[', BRACKET_ML));
    delimeterMap.insert(std::make_pair(']', BRACKET_MR));
    delimeterMap.insert(std::make_pair('(', BRACKET_SL));
    delimeterMap.insert(std::make_pair(')', BRACKET_SR));
    delimeterMap.insert(std::make_pair('.', DOT));
    delimeterMap.insert(std::make_pair(',', COMMA));
    delimeterMap.insert(std::make_pair('{', BRACKET_LL));
    delimeterMap.insert(std::make_pair('}', BRACKET_LR));
    delimeterMap.insert(std::make_pair(';', SEMICOLON));
    
    /* 打开文件 */
    inFileStream.open(fileName.c_str());
    if (!inFileStream.is_open()) {
        std::cout << "can not open the file :" << fileName << std::endl;
        scanError();
    } else {
        getOneLine();
    }
}

/* 实现错误信息处理 */
void Lexer::scanError() {
    Lexer::LEXER_ERROR = 1;
}

/* 读入文件的一行并且存放到lineBuf中 */
void Lexer::getOneLine() {
    lineBuf = "";
    if (!getline(inFileStream, lineBuf)) {
        std::cout << "Error: file end with illegal ending" << std::endl;
    }
    lineBuf += "\n";
}

/* 获得下一个字符 */
char Lexer::getNextChar() {
    if (linePos >= lineBuf.size()) {
        lineNumber ++;
        linePos = 0;
        getOneLine();
        return getNextChar();
    }
    return lineBuf[linePos++];
}

/* 退回一个字符 */
void Lexer::ungetNextChar() {
    if (linePos > 0) {
        linePos--;
    }
}

/* 获得一个Token */
TokenType Lexer::getToken() {
    Lexer::tokenString = "";
    char curChar = getNextChar();
    /* 1.首先获得第一个状态 */
    /* 空格 */
    if (isspace(curChar)) {
        return getToken();
    /* 注释 */
    } else if(curChar == '/') {
        currentState = IN_COMMENT;
    /* 位取反 */
    } else if (curChar == '~') {
        return NOT_BIT;
    /* 界限符 */
    } else if (delimeterMap.find(curChar) != delimeterMap.end()) {
        return delimeterMap[curChar];
    /* 标识符 */
    } else if (isIdentifier(curChar)) {
        currentState = IN_ID;
    /* 单个字符, 单引号 */
    } else if (curChar == '\'') {
        currentState = IN_CONST_CHAR;
    /* 单个字符串, 双引号 */
    } else if (curChar == '"') {
        currentState = IN_CONST_STR;
    /* 数字 */
    } else if (isdigit(curChar)) {
        currentState = IN_NUM;
    /* + */
    } else if (curChar == '+') {
        currentState = IN_ADD;
    /* - */
    } else if (curChar == '-') {
        currentState = IN_MINUS;
    /* * */
    } else if (curChar == '*') {
        currentState = IN_MUL;
    /* /,此种情况已经合并在//中 */
    } else if (curChar == '/') {
    /* % */
    } else if (curChar == '%') {
        currentState = IN_MOD;
    /* & */
    } else if (curChar == '&') {
        currentState = IN_AND;
    /* = */
    } else if (curChar == '=') {
        currentState = IN_ASSIGN;
    /* < */
    } else if (curChar == '<') {
        currentState = IN_LT;
    /* > */
    } else if (curChar == '>') {
        currentState = IN_GT;
    /* | */
    } else if (curChar == '|') {
        currentState = IN_OR;
    /* ! */
    } else if (curChar == '!') {
        currentState = IN_NOT;
    /* ^ */
    } else if (curChar == '^') {
        currentState = IN_XOR;
    }
    /* 2.分别对每一个状态进行处理 */
    while (currentState != DONE) {
        switch (currentState) {
            /* 处理单行以及多行注释 */
            case IN_COMMENT: {
                char next = getNextChar();
                /* 单行注释 */
                if (next == '/') {
                    currentState = DONE;
                    while (getNextChar() != '\n');
                    return getToken();
                    /* 多行注释 */
                } else if (next == '*') {
                    currentState = DONE;
                    while (LEXER_ERROR == 0) {
                        /* 过滤掉注释 */
                        while (getNextChar() != '*' && LEXER_ERROR == 0);
                        if (LEXER_ERROR == 1) {
                            return TOKEN_ERROR;
                        } else {
                            if (getNextChar() == '/' && LEXER_ERROR == 0) {
                                return getToken();
                            }
                        }
                    }
                    return TOKEN_ERROR;
                }
                /* 除号 */
                if (next != '/') {
                    currentState = IN_DIV;
                    ungetNextChar();
                }
                break;
            }
            /* 处理标识符 */
            case IN_ID: {
                currentState = DONE;
                while (isIdentifier(curChar) || isdigit(curChar)) {
                    tokenString += curChar;
                    curChar = getNextChar();
                }
                ungetNextChar();
                /* 判断是否是保留字 */
                if (keyWords.find(tokenString) != keyWords.end()) {
                    return keyWords[tokenString].first;
                }
                break;
            }
            /* 数字 */
            case IN_NUM: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                if (curChar == '0') {
                    if (next == '.') {
                        tokenString.push_back(next);
                        currentState = IN_FLOAT;
                    /* 16进制数字 */
                    } else if (tolower(next) == 'x') {
                        next = getNextChar();
                        while (isdigit(next)) {
                            tokenString.push_back(next);
                            next = getNextChar();
                        }
                        if (next == '.' || tolower(next) == 'e') {
                            tokenString.push_back(next);
                            currentState = IN_FLOAT;
                        } else if (next == 'L') {
                            tokenString.push_back(next);
                            currentState = DONE;
                        } else {
                            ungetNextChar();
                        }
                    }
                    return CONST_INT;
                } else {
                    if (next == '.' || tolower(next) == 'e') {
                        tokenString.push_back(curChar);
                        currentState = IN_FLOAT;
                    } else if (next == 'L') {
                        tokenString.push_back(next);
                        currentState = DONE;
                    } else {
                        ungetNextChar();
                    }
                    return CONST_INT;
                }
                break;
            }
            /* 浮点型 */
            case IN_FLOAT: {
                while (isdigit(curChar)) {
                    tokenString.push_back(curChar);
                    curChar = getNextChar();
                }
                if (tolower(curChar) != 'f') {
                    ungetNextChar();
                }
                return CONST_FLOAT;
                break;
            }
            /* 字符常量 */
            case IN_CONST_CHAR: {
                char next = getNextChar();
                /* 单个字符 */
                if (next != '\\' && next != '\'') {
                    tokenString = next;
                    next = getNextChar();
                    if (next == '\'') {
                        currentState = DONE;
                        return CONST_CHAR;
                    } else {
                        return TOKEN_ERROR;
                    }
                /* 单个单引号 */
                } else if (next == '\'') {
                    currentState = DONE;
                    return CONST_CHAR;
                /* 单个反斜杠, 处理转义字符 */
                } else if (next == '\\') {
                    next = getNextChar();
                    if (next == '\'') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\'");
                    } else if (next == '\\') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\\");
                    } else if (next == 'r') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\r");
                    } else if (next == 'n') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\n");
                    } else if (next == 'f') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\f");
                    } else if (next == 't') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\t");
                    } else if (next == 'b') {
                        tokenString.resize(tokenString.size() - 1);
                        tokenString.append("\b");
                    } else if (next == 'u') {
                        // TODO: \ddd,1-3位8进制字符ddd
                    } else if (isdigit(next)) {
                        // TODO: \uxxxx,1-4位16进制字符xxxx
                    } else {
                        tokenString.push_back(next);
                    }
                }
                return CONST_CHAR;
                break;
            }
            /* 字符常量 */
            case IN_CONST_STR: {
                char next = getNextChar();
                bool convert = false;
                while (next != '\n' && next != '"') {
                    if (convert == false && next == '\\') {
                        convert = true;
                        tokenString.push_back(next);
                    } else if (convert == true) {
                        if (next == '\'') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\'");
                        } else if (next == '\\') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\\");
                        } else if (next == 'r') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\r");
                        } else if (next == 'n') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\n");
                        } else if (next == 'f') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\f");
                        } else if (next == 't') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\t");
                        } else if (next == 'b') {
                            tokenString.resize(tokenString.size() - 1);
                            tokenString.append("\b");
                        } else if (next == 'u') {
                            // TODO: \ddd,1-3位8进制字符ddd
                        } else if (isdigit(next)) {
                            // TODO: \uxxxx,1-4位16进制字符xxxx
                        } else {
                            tokenString.push_back(next);
                        }
                        convert = false;
                    } else {
                        tokenString.push_back(next);
                    }
                    next = getNextChar();
                }
                if (next == '\n') {
                    return TOKEN_ERROR;
                }
                return CONST_STR;
                break;
            }
            /* + */
            case IN_ADD: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* + */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return ADD;
                /* ++ */
                } else if (next == '+') {
                    tokenString.push_back(next);
                    return INC;
                /* += */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return ADD_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* - */
            case IN_MINUS: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* - */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return MINUS;
                /* -- */
                } else if (next == '-') {
                    tokenString.push_back(next);
                    return DEC;
                /* -= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return MINUS_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* * */
            case IN_MUL: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* * */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return MUL;
                /* *= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return MUL_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* / */
            case IN_DIV: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* / */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return DIV;
                    /* /= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return DIV_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* % */
            case IN_MOD: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* % */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return MOD;
                    /* %= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return MOD_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* & */
            case IN_AND: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* & */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return AND_BIT;
                /* && */
                } else if (next == '&') {
                    tokenString.push_back(next);
                    return AND;
                /* &= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return AND_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* = */
            case IN_ASSIGN: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* = */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return ASSIGN;
                /* == */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return EQU;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* | */
            case IN_OR: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* | */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return OR_BIT;
                /* || */
                } else if (next == '|') {
                    tokenString.push_back(next);
                    return OR;
                /* |= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return OR_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* ! */
            case IN_NOT: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* ! */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return NOT;
                /* != */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return NE;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* ^ */
            case IN_XOR: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* ^ */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return XOR;
                /* ^= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return XOR_ASSIGN;
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            /* < */
            case IN_LT: {
                tokenString.push_back(curChar);
                char next = getNextChar();
                /* < */
                if (isdigit(next) || isalpha(next)) {
                    ungetNextChar();
                    return LT;
                /* <= */
                } else if (next == '=') {
                    tokenString.push_back(next);
                    return LE;
                /* << */
                } else if (next == '<') {
                    tokenString.push_back(next);
                    next = getNextChar();
                    if (next == '=') {
                        tokenString.push_back(next);
                        return LEFT_SHIFT_ASSIGN;
                    } else if (isdigit(next) || isalpha(next)) {
                        ungetNextChar();
                        return LEFT_SHIFT;
                    } else {
                        return TOKEN_ERROR;
                    }
                } else {
                    return TOKEN_ERROR;
                }
                break;
            }
            // TODO: GT
            default:
                break;
        }
        
        

    }
}