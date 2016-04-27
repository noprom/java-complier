/****************************************************/
/* File: globals.h                                  */
/* 全局变量的声明,必须在其他文件之前引入                  */
/****************************************************/
#ifndef _GLOBALS_H_
#define  _GLOBALS_H_

#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <cstdio>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXRESERVED 8     /* MAXRESERVED = 保留字的数量 */

typedef enum {
    /* 
     * 特殊的token
     * 文件结束、错误的单词
     */
    ENDFILE, ERROR,
    /**
     * 注释
     */
    COMMENT,
    /**
     * 空格
     */
    SPACE,
    /**
     * 关键字
     * abstract, boolean, break, byte, case, catch, char, class, const, continue,
     * default, do, double, else, extends, false, final, finally, float, for, goto,
     * if, implements, import, instanceof, int, interface, long, native, new, null,
     * package, private, protected, public, return, short, static, super, switch,
     * synchronized, this, throw, throws, transient, true, try, void, volatile, while
     */
    COMMENT,

    /* 保留字 */
    
} TokenType;

extern FILE* source;      /* 源代码文件 */
extern FILE* listing;     /* 中间输出文件 */
extern FILE* code;        /* 代码生成文件 */

extern int lineno;        /* 输出的源代码文件行数 */

#endif
