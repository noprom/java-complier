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

/* 词法分析器的状态 */
typedef enum {
    /**
     * 开始, 结束, 读入标志符, 读入常量, 读入转义符号, 读入界限符
     * 赋值运算符, 关系运算符, 比较运算符, 移位运算符, 计算运算符
     */
    START, DONE, IN_ID, IN_CONST, IN_ESC, IN_DELIMETER,
    IN_OP_ASSIGN, IN_OP_RELATION, IN_OP_CMP, IN_OP_SHIFT, IN_OP_CAL
} DFAStateType;

#endif
