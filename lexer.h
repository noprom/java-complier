//
//  lexer.h
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _LEXER_H
#define _LEXER_H

#include "globals.h"

/* DFA的状态 */
typedef enum {
    /**
     * 开始, 结束, 读入标志符, 读入字符常量, 读入字符串常量, 读入数字, 读入转义符号, 读入界限符, 读入注释
     * 读入+ - * / % & = < > | ! ^
     */
    START, DONE, IN_ID, IN_CONST_CHAR, IN_CONST_STR, IN_NUM, IN_ESC, IN_DELIMETER, IN_COMMENT,
    IN_ADD, IN_MINUS, IN_MUL, IN_DIV, IN_MOD, IN_AND, IN_ASSIGN, IN_LT, IN_GT, IN_OR, IN_NOT, IN_XOR
    
} DFAStateType;

/* 词法分析器类 */
class Lexer {
    
public:
    /* 程序错误标志 */
    static int PROGRAM_ERROR;
    
protected:
    /* 扫描到的行数 */
    static int lineNumber;
    
    /* 扫描到某行的位置 */
    static int linePos;
    
    /* 提取出来的单词 */
    static std::string tokenString;
    
    /**
     * 构造函数
     *
     * @fileName 文件名
     */
    Lexer(std::string fileName);
    
    
};
#endif
