//
//  util.cpp
//  java_complier
//
//  Created by noprom on 4/28/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "util.h"

/* 判断字符是否是字母 */
bool isAlpha(char c) {
	if (tolower(c) >= 'a' && tolower(c) <= 'z') {
		return true;
	}
	return false;
}

/* 判断字符是否是数字 */
bool idDigit(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}

/* 判断否个字符是否是标识符 */
bool isIdentifier(char c) {
	if (isAlpha(c) || c == '_' || c == '$') {
		return true;
	}
	return false;
}

/* 判断字符是否是数值运算符 */
bool isArithmeticOp(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '&' || c == '|' || c == '^') {
		return true;
	}
	return false;
}

/* 判断字符是否是转义字符 */
bool isESC(char c) {
	if (c == '\'' || c == '\\' || c == 'r' || c == 'n' ||
		c == 'f' || c == 't' || c == 'b' || c == 'u') {
		return true;
	}
	return false;
}

/* 数字转化为字符串 */
std::string int2str(int val) {
    char s[20];
    std::string str = "";
    sprintf(s, "%d", val);
    return str + s;
}