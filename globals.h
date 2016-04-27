/****************************************************/
/* File: globals.h                                  */
/* 全局变量的声明,必须在其他文件之前引入                  */
/****************************************************/
#ifndef _GLOBALS_H_
#define  _GLOBALS_H_

#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <string>
#include <cstdio>

//#ifndef FALSE
//#define FALSE 0
//#endif
//
//#ifndef TRUE
//#define TRUE 1
//#endif

/* 定义单词类型 */
typedef enum {
    /* 
     * 特殊的token
     * 文件结束、
     * 错误的单词: 0x100
     */
    ENDFILE, ERROR,
    
    /**
     * 注释: 0x101
     * 空格: 0x102
     */
    COMMENT, SPACE,
    
    /**
     * 标志符: 0x104
     * 整型常量, 实型常量, 布尔常量, 字符串常量, 字符常量
     */
    ID, CONST_NUM, CONST_REAL, CONST_BOOL, CONST_STR, CONST_CHAR,

    /**
     * 关键字: 0x103
     * 布尔型: 0x105
     * 字符型: 0x106
     * 整型:   0x107
     * 浮点型: 0x108
     * 字符串: 0x109
     *
     * abstract, boolean, break, byte, case, catch, char, class, const, continue,
     * default, do, double, else, extends, false, final, finally, float, for, goto,
     * if, implements, import, instanceof, int, interface, long, native, new, null,
     * package, private, protected, public, return, short, static, super, switch,
     * synchronized, this, throw, throws, transient, true, try, void, volatile, while
     */
    ABSTRACT, BOOLEAN, BREAK, BYTE, CASE, CATCH, CHAR, CLASS, CONST, CONTINUE,
    DEFAULT, DO, DOUBLE, ELSE, EXTENDS, FALSE, FINAL, FINALLY, FLOAT, FOR, GOTO,
    IF, IMPLEMENTES, IMPORT, INSTANCEOF, INT, INTERFACE, LONG, NATIVE, NEW, NULL,
    PACKAGE, PRIVATE, PROTECTED, PUBLIC, RETURN, SHORT, STATIC, SUPER, SWITCH,
    SYNCHRONIZED, THIS, THROW, THROWS, TRANSIENT, TRUE, TRY, VOID, VOLATILE, WHILE,
    
    /**
     * 赋值运算符号: 0x110
     * = += -= *= /= %= &=
     * ^= |= >>= <<= >>>=
     */
    ASSIGN, ADD_ASSIGN, MINUS_ASSIGN, MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, AND_ASSIGN,
    XOR_ASSIGN, OR_ASSIGN, RIGHT_SHIFT_ASSIGN, LEFT_SHIFT_ASSIGN, UNSIGNED_RIGHT_SHIRT_ASSIGN,
    
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
    EQU, NE, LT, GT, LE, GE, LEFT_SHIFT, RIGHT_SHIFT, UNSIGNED_RIGHT_SHIRT,
    
    /**
     * 数值计算符号
     * + -                      : 0x11a
     * * / %                    : 0x11b
     * ++ -- +(正) –(负) ! ~     : 0x11c
     */
    ADD, MINUS, MUL, DIV, MOD, INC, DEC, POSITIVE, NEGATIVE, EXCLAMATORY_MARK, NOT,
    
    /**
     * 界限符
     * [] () .                  : 0x11d
     * ,                        : 0x120
     * {}                       : 0x121
     * ;                        : 0x122
     */
    BRACKET_ML, BRACKET_MR, BRACKET_SL, BRACKET_SR, BRACKET_LL, BRACKET_LR, DOT, COMMA, SEMICOLON
    
} TokenType;


extern FILE* source;      /* 源代码文件 */
extern FILE* listing;     /* 中间输出文件 */
extern FILE* code;        /* 代码生成文件 */

extern int lineno;        /* 输出的源代码文件行数 */

#endif
