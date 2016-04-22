/****************************************************/
/* File: globals.h                                  */
/* 全局变量的声明,必须在其他文件之前引入                  */
/****************************************************/
#ifndef _GLOBALS_H_
#define  _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

extern FILE* source;      /* 源代码文件 */
extern FILE* listing;     /* 中间输出文件 */
extern FILE* code;        /* 代码生成文件 */

extern int lineno;        /* 输出的源代码文件行数 */

#endif
