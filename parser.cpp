//
//  parser.cpp
//  java_complier
//
//  Created by noprom on 6/10/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "parser.h"

/* 构造函数 */
//Parser::Parser(std::string fileName) {
//    tokenList.clear();
//    assignStart = false;
//    treeRoot = NULL;
//}

/* 析构函数 */
Parser::~Parser() {
    
}

/* 语法分析 */
TreeNode * Parser::parse() {
    treeRoot = programStmt();
    return treeRoot;
}

/* 整个程序语句 */
TreeNode * Parser::programStmt() {
    /* 这里简化为直接在main函数里面执行 */
    token = Lexer::getToken();
    TreeNode * tempNode = mulSentenceStmt();
    // TODO: handle error
    return tempNode;
}

/* 多语句 */
TreeNode * Parser::mulSentenceStmt() {
    TreeNode * str = NULL;
    TreeNode * end = NULL;
    TreeNode * next = NULL;
    while (token == WHILE || token == SEMICOLON || token == BRACKET_LL || token == BRACKET_LR) {
        next = sentenceStmt();
        /* 第一条语句 */
        if (str == NULL || end == NULL) {
            str = end = next;
        } else {
            end->sibling = next;
            end = next;
        }
    }
    // TODO: handle error
    return str;
}

