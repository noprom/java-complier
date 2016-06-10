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
     *
     * @param fileName 扫描文件名
     */
    Parser(std::string fileName);
    
    /* 析构函数 */
    ~Parser();
    
    /**
     * 生成语法分析树
     *
     * @return 语法树
     **/
    TreeNode* parse();
private:
    
    /**
     * 整个程序的树
     *
     * @return 树的根节点
     */
    TreeNode* programStmt();
    
    /**
     * 多重语句构建的树
     *
     * @return 树的根节点
     */
    TreeNode* mulSentenceStmt();
    
    /**
     * 单条语句构建的树
     *
     * @return 树的根节点
     */
    TreeNode* sentenceStmt();
    
    /**
     * 赋值语句构建的树
     *
     * @return 树的根节点
     */
    TreeNode* assignStmt();
    
    /**
     * while语句构建的树
     *
     * @return 树的根节点
     */
    TreeNode* whileStmt();
    
    /**
     * 多项式语句构建的树
     *
     * @return 树的根节点
     */
    TreeNode* expStmt();
    
    /*
     * 构造简单多项式（无比较符号）语句树
     *
     * @return 树的根节点
     */
    TreeNode* simpleExpStmt(std::list<CompTokenType>::iterator &begin,
                            std::list<CompTokenType>::iterator end);
    
    /*
     * 构造单项式语句树
     *
     * @return 树的根节点
     */
    TreeNode* termStmt(std::list<CompTokenType>::iterator &begin);
    
    /*
     * 构造运算单元树
     *
     * @return 树的根节点
     */
    TreeNode* factorStmt(std::list<CompTokenType>::iterator &begin);
    
    /*
     * 构造语句树时出错的错误处理
     */
    void handleError();
    
    /**
     * 匹配token
     *
     * @param token 要匹配的token
     */
    void match(TokenType token);
    
    /*
     * 删除树节点
     *
     * @param root 待删除的树节点的根节点
     */
    void deleteTreeNode(TreeNode* root);
    
    /* token缓冲区 */
    std::list<TokenType> tokenList;
    
    /* 当前token */
    TokenType token;
    
    /* 赋值语句等号出现标志，将赋值语句与普通多项式区分开 */
    bool assignStart;
    
    /* 语法树根节点 */
    TreeNode* treeRoot;
};
#endif
