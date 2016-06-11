//
//  generator.h
//  java_complier
//
//  Created by noprom on 6/11/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "globals.h"
#include "util.h"

/* 符号表结构 */
typedef struct {
    /* 符号名称 */
    std::string name;
    /* 符号出现的行号 */
    std::vector<int> lineNumbers;
    /* 初始化的值 */
    int initVal;
} SymbolTable;

/* 汇编代码生成类 */
class Generator {
private:
    /* 符号表 */
    std::vector<SymbolTable> symTable;
public:

    /**
     * 由所给的语法树生成符号表
     * 
     * @param syntaxTree 语法树
     */
    void genSymTable(TreeNode * syntaxTree);
    
    /**
     * 生成汇编代码
     * 
     * @param syntaxTree 语法树
     */
    void codeGen(TreeNode * syntaxTree);
};
#endif