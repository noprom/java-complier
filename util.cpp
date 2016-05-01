//
//  util.cpp
//  java_complier
//
//  Created by noprom on 4/28/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "util.h"

/* 判断否个字符是否是标识符 */
bool isIdentifier(char c) {
    if (isalpha(c) || c == '_' || c == '$') {
        return true;
    }
    return false;
}

/* 判断字符是否是数值运算符 */
bool isArithmeticOp(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '^') {
        return true;
    }
    return false;
}