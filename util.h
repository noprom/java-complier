﻿//
//  util.h
//  java_complier
//
//  Created by noprom on 4/28/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _UTIL_H
#define _UTIL_H

#include "globals.h"

/**
* 判断字符是否是字母
* @return 是:true, 否:false
*/
bool isAlpha(char c);

/**
* 判断字符是否是数字
* @return 是:true, 否:false
*/
bool idDigit(char c);

/**
* 判断字符是否是标识符号
* @return 是:true, 否:false
*/
bool isIdentifier(char c);

/**
* 判断字符是否是数值运算符
*/
bool isArithmeticOp(char c);

/**
* 判断字符是否是转义字符
*/
bool isESC(char c);

/**
 * 将数字转化为字符串
 */
std::string int2str(int val);
#endif
