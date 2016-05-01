/****************************************************/
/* File: globals.h                                  */
/* 全局变量的声明,必须在其他文件之前引入                  */
/****************************************************/
#ifndef _GLOBALS_H_
#define  _GLOBALS_H_

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

/* 单词类型 */
typedef enum {
    /*
     * 文件结束
     * 错误的单词: 0x100
     * 注释:      0x101
     * 空格:      0x102
     */
    ENDFILE, TOKEN_ERROR, COMMENT, SPACE,
    
    /**
     * 标志符: 0x104
     * 布尔型: 0x105
     * 字符型: 0x106
     * 整型:   0x107
     * 浮点型: 0x108
     * 字符串: 0x109
     */
    ID, CONST_BOOL, CONST_CHAR, CONST_INT, CONST_FLOAT, CONST_STR, CONST_INT8, CONST_INT16,

    /**
     * 关键字: 0x103
     *
     * abstract, boolean, break, byte, case, catch, char, class, const, continue,
     * default, do, double, else, extends, false, final, finally, float, for, goto,
     * if, implements, import, instanceof, int, interface, long, native, new, null,
     * package, private, protected, public, return, short, static, super, switch,
     * synchronized, this, throw, throws, transient, true, try, void, volatile, while
     */
    ABSTRACT, BOOLEAN, BREAK, BYTE, CASE, CATCH, CHAR, CLASS, CONST, CONTINUE,
    DEFAULT, DO, DOUBLE, ELSE, EXTENDS, JAVA_FALSE, FINAL, FINALLY, FLOAT, FOR, GOTO,
    IF, IMPLEMENTES, IMPORT, INSTANCEOF, INT, INTERFACE, LONG, NATIVE, NEW, JAVA_NULL,
    PACKAGE, PRIVATE, PROTECTED, PUBLIC, RETURN, SHORT, STATIC, SUPER, SWITCH,
    SYNCHRONIZED, THIS, THROW, THROWS, TRANSIENT, JAVA_TRUE, TRY, VOID, VOLATILE, WHILE,
    
    /**
     * 赋值运算符号: 0x110
     * = += -= *= /= %= &=
     * ^= |= >>= <<= >>>=
     */
    ASSIGN, ADD_ASSIGN, MINUS_ASSIGN, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, AND_ASSIGN,
    XOR_ASSIGN, OR_ASSIGN, RIGHT_SHIFT_ASSIGN, LEFT_SHIFT_ASSIGN, ZERO_FILL_RIGHT_SHIRT_ASSIGN,
    
    /**
     * 关系运算符号
     * ?:   0x111
     * ||:  0x112
     * &&:  0x113
     * | :  0x114
     * ^ :  0x115
     * & :  0x116
     */
    TRIPLE_CMP, OR, AND, OR_BIT, XOR, AND_BIT,
    
    /**
     * 比较运算符|移位运算符
     * == !=        : 0x117
     * < > <= >=    : 0x118
     * << >> >>>    : 0x119
     */
    EQU, NE, LT, GT, LE, GE, LEFT_SHIFT, RIGHT_SHIFT, ZERO_FILL_RIGHT_SHIRT,
    
    /**
     * 数值计算符号
     * + -                      : 0x11a
     * * / %                    : 0x11b
     * ++ -- +(正) –(负) ! ~     : 0x11c
     */
    ADD, MINUS, MUL, DIV, MOD, INC, DEC, POSITIVE, NEGATIVE, NOT, NOT_BIT,
    
    /**
     * 界限符
     * [] () .                  : 0x11d
     * ,                        : 0x120
     * {}                       : 0x121
     * ;                        : 0x122
     */
    BRACKET_ML, BRACKET_MR, BRACKET_SL, BRACKET_SR, BRACKET_LL, BRACKET_LR, DOT, COMMA, SEMICOLON
    
} TokenType;


/**
 * TraceSource = 1则输出源代码
 */
extern int TraceSource;

/**
 * TraceScan = 1则输出扫描结果
 */
extern int TraceScan;

#endif
