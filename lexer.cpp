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
    /* 初始化关键字 */
    /** 
     * 关键字: 0x103
     * 布尔型: 0x105
     * 字符型: 0x106
     * 整型:   0x107
     * 浮点型: 0x108
     * 字符串: 0x109
     */
    keyWords.clear();
    keyWords.insert(std::make_pair(ABSTRACT, std::make_pair("abstract", "0x103")));
    keyWords.insert(std::make_pair(BOOLEAN, std::make_pair("boolean", "0x103")));
    keyWords.insert(std::make_pair(BREAK, std::make_pair("break", "0x103")));
    keyWords.insert(std::make_pair(BYTE, std::make_pair("byte", "0x103")));
    keyWords.insert(std::make_pair(CASE, std::make_pair("case", "0x103")));
    keyWords.insert(std::make_pair(CATCH, std::make_pair("catch", "0x103")));
    keyWords.insert(std::make_pair(CHAR, std::make_pair("char", "0x103")));
    keyWords.insert(std::make_pair(CLASS, std::make_pair("class", "0x103")));
    keyWords.insert(std::make_pair(CONST, std::make_pair("const", "0x103")));
    keyWords.insert(std::make_pair(CONTINUE, std::make_pair("continue", "0x103")));
    keyWords.insert(std::make_pair(DEFAULT, std::make_pair("default", "0x103")));
    keyWords.insert(std::make_pair(DO, std::make_pair("do", "0x103")));
    keyWords.insert(std::make_pair(DOUBLE, std::make_pair("double", "0x103")));
    keyWords.insert(std::make_pair(ELSE, std::make_pair("else", "0x103")));
    keyWords.insert(std::make_pair(EXTENDS, std::make_pair("extends", "0x103")));
    keyWords.insert(std::make_pair(JAVA_FALSE, std::make_pair("false", "0x103")));
    keyWords.insert(std::make_pair(FINAL, std::make_pair("final", "0x103")));
    keyWords.insert(std::make_pair(FINALLY, std::make_pair("finally", "0x103")));
    keyWords.insert(std::make_pair(FLOAT, std::make_pair("float", "0x103")));
    keyWords.insert(std::make_pair(FOR, std::make_pair("for", "0x103")));
    keyWords.insert(std::make_pair(GOTO, std::make_pair("goto", "0x103")));
    keyWords.insert(std::make_pair(IF, std::make_pair("if", "0x103")));
    keyWords.insert(std::make_pair(IMPLEMENTES, std::make_pair("implements", "0x103")));
    keyWords.insert(std::make_pair(IMPORT, std::make_pair("import", "0x103")));
    keyWords.insert(std::make_pair(INSTANCEOF, std::make_pair("instanceof", "0x103")));
    keyWords.insert(std::make_pair(INT, std::make_pair("int", "0x103")));
    keyWords.insert(std::make_pair(INTERFACE, std::make_pair("interface", "0x103")));
    keyWords.insert(std::make_pair(LONG, std::make_pair("long", "0x103")));
    keyWords.insert(std::make_pair(NATIVE, std::make_pair("native", "0x103")));
    keyWords.insert(std::make_pair(NEW, std::make_pair("new", "0x103")));
    keyWords.insert(std::make_pair(JAVA_NULL, std::make_pair("null", "0x103")));
    keyWords.insert(std::make_pair(PACKAGE, std::make_pair("package", "0x103")));
    keyWords.insert(std::make_pair(PRIVATE, std::make_pair("private", "0x103")));
    keyWords.insert(std::make_pair(PROTECTED, std::make_pair("protected", "0x103")));
    keyWords.insert(std::make_pair(PUBLIC, std::make_pair("public", "0x103")));
    keyWords.insert(std::make_pair(RETURN, std::make_pair("return", "0x103")));
    keyWords.insert(std::make_pair(SHORT, std::make_pair("short", "0x103")));
    keyWords.insert(std::make_pair(STATIC, std::make_pair("static", "0x103")));
    keyWords.insert(std::make_pair(SUPER, std::make_pair("super", "0x103")));
    keyWords.insert(std::make_pair(SWITCH, std::make_pair("switch", "0x103")));
    keyWords.insert(std::make_pair(SYNCHRONIZED, std::make_pair("synchronized", "0x103")));
    keyWords.insert(std::make_pair(THIS, std::make_pair("this", "0x103")));
    keyWords.insert(std::make_pair(THROW, std::make_pair("throw", "0x103")));
    keyWords.insert(std::make_pair(THROWS, std::make_pair("throws", "0x103")));
    keyWords.insert(std::make_pair(TRANSIENT, std::make_pair("transient", "0x103")));
    keyWords.insert(std::make_pair(JAVA_TRUE, std::make_pair("true", "0x103")));
    keyWords.insert(std::make_pair(TRY, std::make_pair("try", "0x103")));
    keyWords.insert(std::make_pair(VOID, std::make_pair("void", "0x103")));
    keyWords.insert(std::make_pair(VOLATILE, std::make_pair("volatile", "0x103")));
    keyWords.insert(std::make_pair(WHILE, std::make_pair("while", "0x103")));
}



