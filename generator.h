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
#include "lexer.h"

/* 四元式结构 */
typedef struct {
    /* 编号 */
    int no;
    /* 操作符 */
    std::string op;
    /* 参数1 */
    std::string arg1;
    /* 参数2 */
    std::string arg2;
    /* 结果 */
    std::string result;
    /* 以下均为辅助使用 */
    /* 需要回填的编号 */
    int backNo;
} Tuple4;

/* 中间代码生成类 */
class Generator {
private:
    
    /* 用于记录四元式结果项的下标 */
    int resultIndex;
    
    /* 用于记录四元式结果项 */
    std::string result;
    
    /* 最后一个四元式标记 */
    std::string lastResult;
    
    /**
     * 多个语句块
     *
     * @param syntaxTree 语法树
     */
    void mulGen(TreeNode * syntaxTree);
    
    /**
     * 单个语句
     *
     * @param syntaxTree 语法树
     */
    void sentenceGen(TreeNode * syntaxTree);
    
    /**
     * while语句
     *
     * @param syntaxTree 语法树
     */
    void whileGen(TreeNode * syntaxTree);
    
    /**
     * 赋值语句
     *
     * @param syntaxTree 语法树
     */
    void assignGen(TreeNode * syntaxTree);
    
    /**
     * 表达式语句
     *
     * @param syntaxTree 语法树
     */
    void expGen(TreeNode * syntaxTree);
    
    /**
     * 创建一个四元组
     *
     * @param no 编号
     * @param op 运算符号
     * @param arg1 参数1
     * @param arg2 参数2
     * @param result 结果
     * @param backNo 需要回填的编号
     */
    Tuple4 newTuple4(int no, std::string op, std::string arg1, std::string arg2, std::string result, int backNo);
    
    /**
     * 更新结果的数量的下标
     *
     * @param op 操作符
     */
    void updateResultNumber(TokenType op);
    
    /**
     * 更新结果字符串表示形式
     *
     * @param op 操作符
     */
    void updateResultLabel(TokenType op);
    
    /**
     * 具有判断性质的语句执行完成之后
     * 更新跳转到下一条语句的标号
     */
    void updateTuple4();
public:
    
    /* 用于记录四元式列表中的标号 */
    int number;
    
    /* 四元组列表 */
    std::vector<Tuple4> tuple4List;
    
    /* 构造函数 */
    Generator();
    
    /**
     * 生成中间代码
     * 
     * @param syntaxTree 语法树
     */
    void codeGen(TreeNode * syntaxTree);
    
    /**
     * 运行代码生成器
     *
     * @param fileName 要分析的文件
     * @param codeFile 生成目标代码的文件
     */
    static void runGenerator(TreeNode * syntaxTree, std::string fileName, std::string codeFile);
};
#endif