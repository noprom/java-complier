//
//  lexer.cpp
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "lexer.h"

#define KEYWORDS_ID "0x103"

Lexer::Lexer() {

    /* 初始化词法分析器里面的变量 */
    LEXER_ERROR = 0;
    EOF_flag = 0;
    TOKEN_NUM = 0;
    lineNumber = 1;
    lineTokenNum = 0;
    linePos = 0;
    tokenString = "";

    /* 清空用于统计的容器 */
    lineTokenSumMap.clear();
    tokenList.clear();
    errList.clear();
    
    /**
     * 初始化关键字
     * 关键字: 0x103
     */
    keyWords.clear();
    keyWords.insert(std::make_pair("abstract", std::make_pair(ABSTRACT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("boolean", std::make_pair(BOOLEAN, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("break", std::make_pair(BREAK, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("byte", std::make_pair(BYTE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("case", std::make_pair(CASE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("catch", std::make_pair(CATCH, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("char", std::make_pair(CHAR, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("class", std::make_pair(CLASS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("const", std::make_pair(CONST, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("continue", std::make_pair(CONTINUE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("default", std::make_pair(DEFAULT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("do", std::make_pair(DO, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("double", std::make_pair(DOUBLE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("else", std::make_pair(ELSE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("extends", std::make_pair(EXTENDS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("false", std::make_pair(JAVA_FALSE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("final", std::make_pair(FINAL, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("finally", std::make_pair(FINALLY, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("float", std::make_pair(FLOAT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("for", std::make_pair(FOR, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("goto", std::make_pair(GOTO, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("if", std::make_pair(IF, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("implements", std::make_pair(IMPLEMENTES, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("import", std::make_pair(IMPORT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("instanceof", std::make_pair(INSTANCEOF, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("int", std::make_pair(INT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("interface", std::make_pair(INTERFACE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("long", std::make_pair(LONG, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("native", std::make_pair(NATIVE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("new", std::make_pair(NEW, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("null", std::make_pair(JAVA_NULL, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("package", std::make_pair(PACKAGE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("private", std::make_pair(PRIVATE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("protected", std::make_pair(PROTECTED, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("public", std::make_pair(PUBLIC, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("return", std::make_pair(RETURN, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("short", std::make_pair(SHORT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("static", std::make_pair(STATIC, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("super", std::make_pair(SUPER, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("switch", std::make_pair(SWITCH, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("synchronized", std::make_pair(SYNCHRONIZED, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("this", std::make_pair(THIS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("throw", std::make_pair(THROW, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("throws", std::make_pair(THROWS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("transient", std::make_pair(TRANSIENT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("true", std::make_pair(JAVA_TRUE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("try", std::make_pair(TRY, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("void", std::make_pair(VOID, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("volatile", std::make_pair(VOLATILE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("while", std::make_pair(WHILE, KEYWORDS_ID)));
    
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
    tokenMap.insert(std::make_pair(CONST_INT8, std::make_pair("int8 const", "0x107")));
    tokenMap.insert(std::make_pair(CONST_INT16, std::make_pair("int16 const", "0x107")));
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
}

/* 实现构造函数 */
Lexer::Lexer(std::string fileName)
{
    /* 清空用于统计的容器 */
    lineTokenSumMap.clear();
    tokenList.clear();
    errList.clear();
    
    /**
     * 初始化关键字
     * 关键字: 0x103
     */
    keyWords.clear();
    keyWords.insert(std::make_pair("abstract", std::make_pair(ABSTRACT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("boolean", std::make_pair(BOOLEAN, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("break", std::make_pair(BREAK, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("byte", std::make_pair(BYTE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("case", std::make_pair(CASE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("catch", std::make_pair(CATCH, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("char", std::make_pair(CHAR, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("class", std::make_pair(CLASS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("const", std::make_pair(CONST, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("continue", std::make_pair(CONTINUE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("default", std::make_pair(DEFAULT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("do", std::make_pair(DO, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("double", std::make_pair(DOUBLE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("else", std::make_pair(ELSE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("extends", std::make_pair(EXTENDS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("false", std::make_pair(JAVA_FALSE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("final", std::make_pair(FINAL, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("finally", std::make_pair(FINALLY, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("float", std::make_pair(FLOAT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("for", std::make_pair(FOR, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("goto", std::make_pair(GOTO, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("if", std::make_pair(IF, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("implements", std::make_pair(IMPLEMENTES, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("import", std::make_pair(IMPORT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("instanceof", std::make_pair(INSTANCEOF, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("int", std::make_pair(INT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("interface", std::make_pair(INTERFACE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("long", std::make_pair(LONG, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("native", std::make_pair(NATIVE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("new", std::make_pair(NEW, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("null", std::make_pair(JAVA_NULL, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("package", std::make_pair(PACKAGE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("private", std::make_pair(PRIVATE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("protected", std::make_pair(PROTECTED, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("public", std::make_pair(PUBLIC, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("return", std::make_pair(RETURN, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("short", std::make_pair(SHORT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("static", std::make_pair(STATIC, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("super", std::make_pair(SUPER, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("switch", std::make_pair(SWITCH, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("synchronized", std::make_pair(SYNCHRONIZED, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("this", std::make_pair(THIS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("throw", std::make_pair(THROW, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("throws", std::make_pair(THROWS, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("transient", std::make_pair(TRANSIENT, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("true", std::make_pair(JAVA_TRUE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("try", std::make_pair(TRY, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("void", std::make_pair(VOID, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("volatile", std::make_pair(VOLATILE, KEYWORDS_ID)));
    keyWords.insert(std::make_pair("while", std::make_pair(WHILE, KEYWORDS_ID)));
    
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
    tokenMap.insert(std::make_pair(CONST_INT8, std::make_pair("int8 const", "0x107")));
    tokenMap.insert(std::make_pair(CONST_INT16, std::make_pair("int16 const", "0x107")));
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
    
	ifs.open(fileName);
	/* 打开文件 */
	if (!ifs.is_open()) {
		printf("can not open the file : %s\n", fileName.c_str());
		scanError();
		exit(1);
	}
	else {
		getOneLine();
	}
}

Lexer::~Lexer(){
	return;
}

/* 实现错误信息处理 */
void Lexer::scanError() {
	Lexer::LEXER_ERROR = 1;
}

/* 读入文件的一行并且存放到lineBuf中 */
void Lexer::getOneLine() {
	/* 初始化每行统计变量 */
	lineBuf = "";
	//if (!ifs->eof()) {
		if (!getline(ifs, lineBuf)) {
			// std::cout << "Error: file end with illegal ending" << std::endl;
			Lexer::LEXER_ERROR = 1;
			EOF_flag = 1;
		}
		
	//}
	//else {
	//	EOF_flag = 1;
	//}

	lineBuf += "\n";
	if (TraceSource) {
		printf("%4d: %s\n", lineNumber, lineBuf.c_str());
	}
}

/* 获得下一个字符 */
char Lexer::getNextChar() {
	if (linePos >= lineBuf.size()) {
		/* 保存统计结果 */
		lineTokenSumMap.insert(std::make_pair(lineNumber, lineTokenNum));
		/* 重新开始下一行 */
		lineNumber++;
		lineTokenNum = 0;
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

/* 打印token的信息 */
void Lexer::printToken(TokenType token, std::string tokenString) {
	std::string tokenName = tokenMap[token].first;
	std::string tokenID = tokenMap[token].second;
	if (keyWords.find(tokenString) != keyWords.end()) {
		tokenName = "keywords";
		tokenID = keyWords[tokenString].second;
	}

	/* 调试输出到控制台 */
	printf("%15s \t %15s \t %10s\n", tokenName.c_str(), tokenString.c_str(), tokenID.c_str());
}

/* 获得token的类型名称 */
std::string Lexer::getTokenTypeName(TokenType type, std::string tokenString) {
	std::string typeName = "";
	/* 1.是否是关键字 */
	if (keyWords.find(tokenString) != keyWords.end()) {
		typeName = "keywords";
		/* 2.是否是界限符 */
	}
	else if (delimeterMap.find(tokenString[0]) != delimeterMap.end()) {
		typeName = "delimeter";
		/* 3.是否是标识符 */
	}
	else if (type == ID) {
		typeName = "identifier";
	}
	else {
		switch (type) {
			/* 4.是否是常量 */
		case CONST_INT:
			typeName = "int const";
			break;
		case CONST_FLOAT:
			typeName = "float const";
			break;
		case CONST_BOOL:
			typeName = "bool const";
			break;
		case CONST_CHAR:
			typeName = "char const";
			break;
		case CONST_STR:
			typeName = "string const";
			break;
			/* 5.否则默认位运算符 */
		default:
			if (type != TOKEN_ERROR) {
				typeName = "operator";
			}
			else {
				typeName = "token error";
			}
			break;
		}
	}
	return typeName;
}

/* 创建一个新的token */
Token Lexer::createToken(TokenType type, std::string tokenString) {
	Token *token = new Token;
	token->lineNumber = lineNumber;
	token->type = type;
	token->typeName = getTokenTypeName(type, tokenString);
	token->value = tokenString;
	/* 获得关键字属性 */
	if (keyWords.find(tokenString) != keyWords.end()) {
		token->attr = KEYWORDS_ID;
	}
	else {
		token->attr = tokenMap[type].second;
	}
	return *token;
}

/* 创建一个token出错的错误信息 */
TokenErrorInfo Lexer::createTokenErrorInfo(std::string errorToken) {
	TokenErrorInfo *err = new TokenErrorInfo;
	err->lineNumber = lineNumber;
	err->errorPos = linePos;
	err->lineBuf = lineBuf;
	err->errorToken = errorToken;
	return *err;
}

/* 获得一个Token */
TokenType Lexer::getToken() {
	if (Lexer::LEXER_ERROR == 1) {
		return ENDFILE;
	}
	Lexer::tokenString = "";
	char curChar = getNextChar();
	TokenType currentToken = TOKEN_ERROR;

	if (EOF_flag) {
		return ENDFILE;
	}
	/* 1.首先获得第一个状态 */
	/* 空格 */
	if (curChar == ' ' || curChar == '\r' || curChar == '\n' || curChar == '\t') {
		return getToken();
		/* 注释 */
	}
	else if (curChar == '/') {
		currentState = IN_COMMENT;
		/* 位取反 */
	}
	else if (curChar == '~') {
		tokenString.push_back(curChar);
		currentState = DONE;
		currentToken = NOT_BIT;
		/* 界限符 */
    } else if (curChar == ';') {
        tokenString.push_back(curChar);
        currentState = DONE;
        currentToken = SEMICOLON;
    } else if (curChar == '(') {
        tokenString.push_back(curChar);
        currentState = DONE;
        currentToken = BRACKET_SL;
    } else if (curChar == ')') {
        tokenString.push_back(curChar);
        currentState = DONE;
        currentToken = BRACKET_SR;
    }
	else if (delimeterMap.find(curChar) != delimeterMap.end()) {
		tokenString.push_back(curChar);
		currentState = DONE;
		currentToken = delimeterMap[curChar];
		/* 标识符 */
	}
	else if (isIdentifier(curChar)) {
		currentState = IN_ID;
		/* 单个字符, 单引号 */
	}
	else if (curChar == '\'') {
		currentState = IN_CONST_CHAR;
		/* 单个字符串, 双引号 */
	}
	else if (curChar == '"') {
		currentState = IN_CONST_STR;
		/* 数字 */
	}
	else if (idDigit(curChar)) {
		currentState = IN_INT;
		/* + */
	}
	else if (curChar == '+') {
		currentState = IN_ADD;
		/* - */
	}
	else if (curChar == '-') {
		currentState = IN_MINUS;
		/* * */
	}
	else if (curChar == '*') {
		currentState = IN_MUL;
		/* /,此种情况已经合并在//中 */
	}
	else if (curChar == '/') {
		/* % */
	}
	else if (curChar == '%') {
		currentState = IN_MOD;
		/* & */
	}
	else if (curChar == '&') {
		currentState = IN_AND;
		/* = */
	}
	else if (curChar == '=') {
		currentState = IN_ASSIGN;
		/* < */
	}
	else if (curChar == '<') {
		currentState = IN_LT;
		/* > */
	}
	else if (curChar == '>') {
		currentState = IN_GT;
		/* | */
	}
	else if (curChar == '|') {
		currentState = IN_OR;
		/* ! */
	}
	else if (curChar == '!') {
		currentState = IN_NOT;
		/* ^ */
	}
	else if (curChar == '^') {
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
							 }
							 else if (next == '*') {
								 currentState = DONE;
								 while (LEXER_ERROR == 0) {
									 /* 过滤掉注释 */
									 while (getNextChar() != '*' && LEXER_ERROR == 0);
									 if (LEXER_ERROR == 1) {
										 return TOKEN_ERROR;
									 }
									 else {
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
						while (isIdentifier(curChar) || idDigit(curChar)) {
							tokenString += curChar;
							curChar = getNextChar();
						}
						ungetNextChar();
						/* 判断是否是关键字 */
						if (keyWords.find(tokenString) != keyWords.end()) {
							currentToken = keyWords[tokenString].first;
						}
						else {
							currentToken = ID;
						}
						break;
		}
			/* 数字 */
		case IN_INT: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 if (curChar == '0') {
							 /* 0开头的浮点数 */
							 if (next == '.') {
								 tokenString.push_back(next);
								 currentState = IN_FLOAT;
								 break;
								 /* 8进制数字 */
							 }
							 else if (next >= '0' && next <= '7') {
								 tokenString.push_back(next);
								 currentState = IN_INT8;
								 break;
								 /* 16进制数字 */
							 }
							 else if (tolower(next) == 'x') {
								 tokenString.push_back(next);
								 next = getNextChar();
								 if (idDigit(next) || (tolower(next) >= 'a' && tolower(next) <= 'f')) {
									 tokenString.push_back(next);
									 currentState = IN_INT16;
									 break;
								 }
								 else {
									 currentState = DONE;
									 currentToken = TOKEN_ERROR;
									 break;
								 }
								 /* 纯粹就是数字0 */
							 }
							 else if (isspace(next) || tolower(next) == 'l') {
								 currentState = DONE;
								 currentToken = CONST_INT;
								 if (tolower(next) == 'l') {
									 tokenString.push_back(next);
								 }
								 break;
								 /* 后面接上合法的运算符号 */
							 }
							 else if (next == ';' || next == ']' || next == ')' || isArithmeticOp(next)) {
								 currentState = DONE;
								 currentToken = CONST_INT;
								 ungetNextChar();
								 break;
								 /* 否则出现词法错误 */
							 }
							 else {
								 currentState = DONE;
								 currentToken = TOKEN_ERROR;
								 break;
							 }
						 }
						 else {
							 /* 10进制数字 */
							 while (idDigit(next)) {
								 tokenString.push_back(next);
								 next = getNextChar();
							 }
							 /* 10进制浮点数 */
							 if (next == '.') {
								 tokenString.push_back(next);
								 currentState = IN_FLOAT;
								 break;
								 /* 10进制整数long型 */
							 }
							 else if (isspace(next) || tolower(next) == 'l') {
								 currentState = DONE;
								 currentToken = CONST_INT;
								 if (tolower(next) == 'l') {
									 tokenString.push_back(next);
								 }
								 break;
								 /* 10进制科学技术法表示 */
							 }
							 else if (tolower(next) == 'e') {
								 tokenString.push_back(next);
								 next = getNextChar();
								 if (idDigit(next)) {
									 tokenString.push_back(next);
									 currentState = IN_FLOAT;
									 break;
								 }
								 else {
									 tokenString.pop_back();
									 currentState = DONE;
									 currentToken = TOKEN_ERROR;
									 break;
								 }
								 /* 后面接上合法的运算符号 */
							 }
							 else if (next == ';' || next == ']' || next == ')' || isArithmeticOp(next)) {
								 currentState = DONE;
								 currentToken = CONST_INT;
								 ungetNextChar();
								 break;
								 /* 否则出现词法错误 */
							 }
							 else {
								 currentState = DONE;
								 currentToken = TOKEN_ERROR;
								 break;
							 }
						 }
						 break;
		}
			/* 8进制数字 */
		case IN_INT8: {
						  char next = getNextChar();
						  while (idDigit(next) && next <= '7') {
							  tokenString.push_back(next);
							  next = getNextChar();
						  }
						  /* 8进制小数 */
						  if (next == '.') {
							  tokenString.push_back(next);
							  next = getNextChar();
							  /* 8进制小数,科学计数法 */
							  if (tolower(next) == 'e') {
								  tokenString.push_back(next);
								  next = getNextChar();
								  if (idDigit(next)) {
									  tokenString.push_back(next);
									  currentState = IN_FLOAT;
									  break;
								  }
								  else {
									  tokenString.pop_back();
									  currentState = DONE;
									  currentToken = TOKEN_ERROR;
									  break;
								  }
								  /* 普通8进制小数 */
							  }
							  else if (isspace(next)) {
								  currentState = DONE;
								  currentToken = CONST_FLOAT;
								  break;
							  }
							  else if (idDigit(next)) {
								  tokenString.push_back(next);
								  currentState = IN_FLOAT;
								  break;
								  /* 后面接上合法的运算符号 */
							  }
							  else if (next == ';' || next == ']' || next == ')' || isArithmeticOp(next)) {
								  currentState = DONE;
								  currentToken = CONST_FLOAT;
								  ungetNextChar();
								  break;
								  /* 否则出现词法错误 */
							  }
							  else {
								  currentState = DONE;
								  currentToken = TOKEN_ERROR;
								  break;
							  }
							  /* 8进制整数 */
						  }
						  else if (isspace(next)) {
							  currentState = DONE;
							  currentToken = CONST_INT8;
							  break;
							  /* 后面接上合法的运算符号 */
						  }
						  else if (next == ';' || next == ']' || next == ')' || isArithmeticOp(next)) {
							  currentState = DONE;
							  currentToken = CONST_INT8;
							  ungetNextChar();
							  break;
							  /* 否则出现词法错误 */
						  }
						  else {
							  currentState = DONE;
							  currentToken = TOKEN_ERROR;
							  break;
						  }
						  break;
		}
			/* 16进制数字 */
		case IN_INT16: {
						   char next = getNextChar();
						   while (idDigit(next) || ('a' <= tolower(next) && tolower(next) <= 'f')) {
							   tokenString.push_back(next);
							   next = getNextChar();
						   }
						   /* 纯粹16进制数字 */
						   if (isspace(next)) {
							   currentState = DONE;
							   currentToken = CONST_INT16;
							   break;
						   }
						   else if (next == ';' || next == ']' || next == ')' || isArithmeticOp(next)) {
							   currentState = DONE;
							   currentToken = CONST_INT16;
							   ungetNextChar();
							   break;
							   /* 否则出现词法错误 */
						   }
						   else {
							   currentState = DONE;
							   currentToken = TOKEN_ERROR;
							   break;
						   }
						   break;
		}
			/* 浮点型 */
		case IN_FLOAT: {
						   char next = getNextChar();
						   while (idDigit(next)) {
							   tokenString.push_back(next);
							   next = getNextChar();
						   }
						   if (tolower(next) != 'f') {
							   ungetNextChar();
						   }
						   else {
							   tokenString.push_back(next);
						   }
						   currentState = DONE;
						   currentToken = CONST_FLOAT;
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
										currentToken = CONST_CHAR;
									}
									else {
										currentToken = TOKEN_ERROR;
									}
									/* 单个单引号 */
								}
								else if (next == '\'') {
									currentState = DONE;
									currentToken = CONST_CHAR;
									/* 单个反斜杠, 处理转义字符 */
								}
								else if (next == '\\') {
									next = getNextChar();
									if (next == '\'') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\'");
									}
									else if (next == '\\') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\\");
									}
									else if (next == 'r') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\r");
									}
									else if (next == 'n') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\n");
									}
									else if (next == 'f') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\f");
									}
									else if (next == 't') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\t");
									}
									else if (next == 'b') {
										tokenString.resize(tokenString.size() - 1);
										tokenString.append("\b");
									}
									else if (next == 'u') {
										// TODO: \ddd,1-3位8进制字符ddd
									}
									else if (idDigit(next)) {
										// TODO: \uxxxx,1-4位16进制字符xxxx
									}
									else {
										tokenString.push_back(next);
									}
								}
								currentState = DONE;
								currentToken = CONST_CHAR;
								break;
		}
			/* 字符串常量 */
		case IN_CONST_STR: {
							   char next = getNextChar();
							   bool convert = false;
							   while (next != '\n' && next != '"') {
								   if (convert == false && next == '\\') {
									   convert = true;
									   tokenString.push_back(next);
								   }
								   else if (convert == true) {
									   if (next == '\'') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\'");
									   }
									   else if (next == '\\') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\\");
									   }
									   else if (next == 'r') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\r");
									   }
									   else if (next == 'n') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\n");
									   }
									   else if (next == 'f') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\f");
									   }
									   else if (next == 't') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\t");
									   }
									   else if (next == 'b') {
										   tokenString.resize(tokenString.size() - 1);
										   tokenString.append("\b");
										   /* \ddd,1-3位8进制字符ddd */
									   }
									   else if (idDigit(next)) {
										   tokenString.push_back(next);
										   int cnt = 0;
										   next = getNextChar();
										   while (idDigit(next)) {
											   tokenString.push_back(next);
											   next = getNextChar();
											   cnt++;
										   }
										   ungetNextChar();
										   if (cnt > 3) {
											   currentState = DONE;
											   currentToken = TOKEN_ERROR;
											   break;
										   }
										   /* \uxxxx,1-4位16进制字符xxxx */
									   }
									   else if (next == 'u') {
										   tokenString.push_back(next);
										   next = getNextChar();
										   int cnt = 0;
										   while (idDigit(next)) {
											   tokenString.push_back(next);
											   next = getNextChar();
											   cnt++;
										   }
										   ungetNextChar();
										   if (cnt > 4) {
											   currentState = DONE;
											   currentToken = TOKEN_ERROR;
											   break;
										   }
									   }
									   else {
										   tokenString.push_back(next);
									   }
									   convert = false;
								   }
								   else {
									   tokenString.push_back(next);
								   }
								   next = getNextChar();
							   }
							   if (next == '\n') {
								   currentState = DONE;
								   currentToken = TOKEN_ERROR;
							   }
							   currentState = DONE;
							   currentToken = CONST_STR;
							   break;
		}
			/* 负数 */
		case IN_NEGATIVE: {
							  tokenString.push_back('-');
							  char next = getNextChar();
							  while (isspace(next)) {
								  next = getNextChar();
							  }
							  if (idDigit(next)) {
								  tokenString.push_back(next);
								  currentState = IN_INT;
							  }
							  else {
								  currentState = DONE;
								  currentToken = TOKEN_ERROR;
							  }
							  break;
		}
			/* + */
		case IN_ADD: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* + */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = ADD;
							 /* ++ */
						 }
						 else if (next == '+') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = INC;
							 /* += */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = ADD_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* - */
		case IN_MINUS: {
						   tokenString.push_back(curChar);
						   char next = getNextChar();
						   /* 减号 */
						   if (idDigit(next) || isAlpha(next) || isspace(next)) {
							   ungetNextChar();
							   currentState = DONE;
							   currentToken = MINUS;
							   /* -- */
						   }
						   else if (next == '-') {
							   tokenString.push_back(next);
							   currentState = DONE;
							   currentToken = DEC;
							   /* -= */
						   }
						   else if (next == '=') {
							   tokenString.push_back(next);
							   currentState = DONE;
							   currentToken = MINUS_ASSIGN;
						   }
						   else {
							   currentState = DONE;
							   currentToken = TOKEN_ERROR;
						   }
						   break;
		}
			/* * */
		case IN_MUL: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* * */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = MUL;
							 /* *= */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = MUL_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* / */
		case IN_DIV: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* / */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = DIV;
							 /* /= */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = DIV_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* % */
		case IN_MOD: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* % */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = MOD;
							 /* %= */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = MOD_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* & */
		case IN_AND: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* & */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = AND_BIT;
							 /* && */
						 }
						 else if (next == '&') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = AND;
							 /* &= */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = AND_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* = */
		case IN_ASSIGN: {
							tokenString.push_back(curChar);
							char next = getNextChar();
							/* = */
							if (idDigit(next) || isAlpha(next) || isspace(next)) {
								ungetNextChar();
								currentState = DONE;
								currentToken = ASSIGN;
								/* == */
							}
							else if (next == '=') {
								tokenString.push_back(next);
								currentState = DONE;
								currentToken = EQU;
							}
							else {
								currentState = DONE;
								currentToken = TOKEN_ERROR;
							}
							break;
		}
			/* | */
		case IN_OR: {
						tokenString.push_back(curChar);
						char next = getNextChar();
						/* | */
						if (idDigit(next) || isAlpha(next) || isspace(next)) {
							ungetNextChar();
							currentState = DONE;
							currentToken = OR_BIT;
							/* || */
						}
						else if (next == '|') {
							tokenString.push_back(next);
							currentState = DONE;
							currentToken = OR;
							/* |= */
						}
						else if (next == '=') {
							tokenString.push_back(next);
							currentState = DONE;
							currentToken = OR_ASSIGN;
						}
						else {
							currentState = DONE;
							currentToken = TOKEN_ERROR;
						}
						break;
		}
			/* ! */
		case IN_NOT: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* ! */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = NOT;
							 /* != */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = NE;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* ^ */
		case IN_XOR: {
						 tokenString.push_back(curChar);
						 char next = getNextChar();
						 /* ^ */
						 if (idDigit(next) || isAlpha(next) || isspace(next)) {
							 ungetNextChar();
							 currentState = DONE;
							 currentToken = XOR;
							 /* ^= */
						 }
						 else if (next == '=') {
							 tokenString.push_back(next);
							 currentState = DONE;
							 currentToken = XOR_ASSIGN;
						 }
						 else {
							 currentState = DONE;
							 currentToken = TOKEN_ERROR;
						 }
						 break;
		}
			/* < */
		case IN_LT: {
						tokenString.push_back(curChar);
						char next = getNextChar();
						/* < */
						if (idDigit(next) || isAlpha(next) || isspace(next)) {
							ungetNextChar();
							currentState = DONE;
							currentToken = LT;
							/* <= */
						}
						else if (next == '=') {
							tokenString.push_back(next);
							currentState = DONE;
							currentToken = LE;
							/* << */
						}
						else if (next == '<') {
							tokenString.push_back(next);
							next = getNextChar();
							if (next == '=') {
								tokenString.push_back(next);
								currentState = DONE;
								currentToken = LEFT_SHIFT_ASSIGN;
							}
							else if (idDigit(next) || isAlpha(next) || isspace(next)) {
								ungetNextChar();
								currentState = DONE;
								currentToken = LEFT_SHIFT;
							}
							else {
								currentState = DONE;
								currentToken = TOKEN_ERROR;
							}
						}
						else {
							currentState = DONE;
							currentToken = TOKEN_ERROR;
						}
						break;
		}
			/* > */
		case IN_GT: {
						tokenString.push_back(curChar);
						char next = getNextChar();
						/* > */
						if (idDigit(next) || isAlpha(next) || isspace(next)) {
							ungetNextChar();
							currentState = DONE;
							currentToken = GT;
							/* >= */
						}
						else if (next == '=') {
							tokenString.push_back(next);
							currentState = DONE;
							currentToken = GE;
							/* >> */
						}
						else if (next == '>') {
							tokenString.push_back(next);
							next = getNextChar();
							/* >>= */
							if (next == '=') {
								tokenString.push_back(next);
								currentState = DONE;
								currentToken = RIGHT_SHIFT_ASSIGN;
								/* >> */
							}
							else if (idDigit(next) || isAlpha(next) || isspace(next)) {
								ungetNextChar();
								currentState = DONE;
								currentToken = RIGHT_SHIFT;
								/* >>> */
							}
							else if (next == '>') {
								tokenString.push_back(next);
								next = getNextChar();
								/* >>>= */
								if (next == '=') {
									tokenString.push_back(next);
									currentState = DONE;
									currentToken = ZERO_FILL_RIGHT_SHIRT_ASSIGN;
									/* >>> */
								}
								else if (idDigit(next) || isAlpha(next) || isspace(next)) {
									ungetNextChar();
									currentState = DONE;
									currentToken = ZERO_FILL_RIGHT_SHIRT;
								}
								else {
									currentState = DONE;
									currentToken = TOKEN_ERROR;
								}
							}
							else {
								currentState = DONE;
								currentToken = TOKEN_ERROR;
							}
						}
						else {
							currentState = DONE;
							currentToken = TOKEN_ERROR;
						}
						break;
		}
		default:
			currentState = DONE;
			currentToken = TOKEN_ERROR;
			break;
		}
	}
	/* 输出状态转化完毕之后的结果 */
	if (TraceScan) {
		if (TraceSource) {
			printf("\t4%d: ", lineNumber);
		}
		else {
			printf("%4d: ", lineNumber);
		}
		printToken(currentToken, tokenString);
	}
	/* 保存token的信息 */
	Token token = createToken(currentToken, tokenString);
	tokenList.push_back(token);
	/* 统计错误信息 */
	if (currentToken == TOKEN_ERROR) {
		TokenErrorInfo err = createTokenErrorInfo(tokenString);
		errList.push_back(err);
		getOneLine();
	}
	/* 累加总单词个数 */
	TOKEN_NUM++;
	/* 累加每行单词个数 */
	lineTokenNum++;
	return currentToken;
}

/* 运行词法分析器 */
void Lexer::runLexer(std::string fileName, std::string outFileName) {
    /* 开始词法分析 */
    Lexer lexer(fileName);
    TokenType token = lexer.getToken();
    while (token != ENDFILE) {
        token = lexer.getToken();
    }
    
    /* 输出到文件 */
    FILE *fp = fopen(outFileName.c_str(), "w");
    
    /* 输出统计结果 */
    printf("Total tokens: %d\n", lexer.TOKEN_NUM);
    fprintf(fp, "Total tokens: %d\n", lexer.TOKEN_NUM);
    for (std::map<int, int>::iterator it = lexer.lineTokenSumMap.begin();
         it != lexer.lineTokenSumMap.end(); ++it) {
        std::pair<int, int> pair = *it;
        if (pair.second > 1) {
            printf("%5d:%5d\t tokens\n", pair.first, pair.second);
            fprintf(fp, "%5d:%5d\t tokens\n", pair.first, pair.second);
        }
        else {
            printf("%5d:%5d\t token\n", pair.first, pair.second);
            fprintf(fp, "%5d:%5d\t token\n", pair.first, pair.second);
        }
    }
    
    /* 输出提示字符串 */
    printf("\n\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+                      Scan Result                  +\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n\n");
    
    /* 输出扫描结果 */
    for (std::vector<Token>::iterator it = lexer.tokenList.begin();
         it != lexer.tokenList.end(); ++it) {
        Token token = *it;
        printf("%4d: %15s \t %15s \t %10s\n", token.lineNumber, token.value.c_str(), token.typeName.c_str(), token.attr.c_str());
        fprintf(fp, "%4d: %15s \t %15s \t %10s\n", token.lineNumber, token.value.c_str(), token.typeName.c_str(), token.attr.c_str());
    }
    
    /* 输出错误信息列表 */
    for (std::vector<TokenErrorInfo>::iterator it = lexer.errList.begin();
         it != lexer.errList.end(); ++it) {
        TokenErrorInfo err = *it;
        printf("Error line: %4d, %s", err.lineNumber, err.lineBuf.c_str());
        printf("Error position: %d, error token: %s\n", err.errorPos, err.errorToken.c_str());
        fprintf(fp, "Error line: %4d, %s", err.lineNumber, err.lineBuf.c_str());
        fprintf(fp, "Error position: %d, error token: %s\n", err.errorPos, err.errorToken.c_str());
    }
    /* 关闭打开的文件 */
    lexer.ifs.close();
    fclose(fp);
}