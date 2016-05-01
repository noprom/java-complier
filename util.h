//
//  util.hpp
//  java_complier
//
//  Created by noprom on 4/28/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _UTIL_H
#define _UTIL_H

#include "globals.h"

/**
 * 判断字符是否是标识符号
 * @return 是:true, 否:false
 */
bool isIdentifier(char c);

/**
 * 判断字符是否是数值运算符
 */
bool isArithmeticOp(char c);
#endif
