//
//  parser.h
//  java_complier
//
//  Created by noprom on 6/10/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _PARSER_H
#define _PARSER_H
#include "lexer.h"

/* 组合token */
typedef struct {
    TokenType type;
    std::string str;
} CompTokenType;

class Parser {
public:
    
    /**
     * 构造函数
     * @param fileName 扫描文件名
     */
    Parser(std::string fileName);
    
    
private:
};
#endif
