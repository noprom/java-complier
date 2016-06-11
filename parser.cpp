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

/* 单个语句 */
TreeNode * Parser::sentenceStmt() {
    Parser::tokenList.clear();
    switch (token) {
        case WHILE:
            whileStmt();
            break;
        case ID:
            assignStart = true;
            return assignStmt();
            break;
        // TODO: handle error
        default:
            return NULL;
            break;
    }
    return NULL;
}

/* 赋值语句 */
TreeNode * Parser::assignStmt() {
    Parser::tokenList.clear();
    // TODO: handle error
    TreeNode *treeNode = new TreeNode;
    TreeNode &thisNode = *treeNode;
    thisNode.lineno = lineNumber;
    /* 连等尚未开始 */
    if (assignStart == false) {
        /* 初始化节点信息 */
        thisNode.nodeKind = STMTK;
        thisNode.stmtKind = ASSIGNK;
        thisNode.id = tokenString;
        token = getToken();
        match(ASSIGN);
        /* 开始赋值符号 */
        assignStart = true;
        token = getToken();
        /* 多项式运算里面可能出现的符号 */
        if (token == ID || token == CONST_INT || token == CONST_INT8 || token == CONST_INT16
            || token == ADD || token == MINUS || token == MUL || token == DIV || token == BRACKET_LL || token == BRACKET_LR) {
            thisNode.child.clear();
            thisNode.child.push_back(assignStmt());
        } else {
            // TODO: handle error
        }
    } else {
        /* 开始连等运算 */
        Parser::tokenList.push_back({token, tokenString});
        thisNode.id = tokenString;
        token = getToken();
        /* 如果连等继续 */
        if (token == ASSIGN && (tokenList.back().type == ID)) {
            tokenList.clear();
            token = getToken();
            thisNode.nodeKind = STMTK;
            thisNode.stmtKind = ASSIGNK;
            thisNode.child.clear();
            thisNode.child.push_back(assignStmt());
        } else {
            /* 最后一个是表达式 */
            delete (treeNode);
            TreeNode * tmpExp = expStmt();
            match(SEMICOLON);
            token = getToken();
            // TODO: handle error
            return tmpExp;
        }
    }
    // TODO: handle error
    return treeNode;
}

/* While语句 */
TreeNode * Parser::whileStmt() {
    // TODO: handle error
    TreeNode * treeNode = new TreeNode;
    TreeNode & thisNode = *treeNode;
    thisNode.lineno = lineNumber;
    thisNode.nodeKind = STMTK;
    thisNode.stmtKind = WHILEK;
    thisNode.child.clear();
    // 匹配while语句
    token = getToken();
    match(BRACKET_SL);
    token = getToken();
    // ()中的表达式语句
    Parser::tokenList.clear();
    thisNode.child.push_back(expStmt());
    match(BRACKET_SR);
    token = getToken();
    // 暂时处理单个赋值语句
    thisNode.child.push_back(assignStmt());
    // TODO: handle error
    return treeNode;
}

/* 表达式语句 */
TreeNode * Parser::expStmt() {
    // TODO: handle error
    while (token == ID || token == CONST_INT || token == CONST_INT8 || token == CONST_INT16 ||
           token == ADD || token == MINUS || token == MUL || token == DIV || token == MOD ||
           token == GT || token == LT || token == GE || token == LE || token == NE || token == EQU) {
        Parser::tokenList.push_back({token, tokenString});
        token = getToken();
    }
    // 遍历表达式语句中的节点
    std::list<CompTokenType>::iterator iter = Parser::tokenList.begin();
    std::list<CompTokenType>::iterator begin = Parser::tokenList.begin();
    std::list<CompTokenType>::iterator end = Parser::tokenList.end();
    // 遍历到比较符号结束
    while (iter != end && iter->type != GT && iter->type != LT &&
           iter->type != GE && iter->type != LE && iter->type != NE && iter->type != EQU) {
        iter++;
    }
    /* 不是比较语句 */
    if (iter == tokenList.end()) {
        return simpleExpStmt(begin, end);
    } else {
        TreeNode * treeNode = new TreeNode;
        TreeNode & thisNode = * treeNode;
        /* 初始化该节点 */
        thisNode.lineno = lineNumber;
        thisNode.nodeKind = EXPK;
        thisNode.expK = OPK;
        thisNode.op = iter->type;
        /* 将左右两个子树作为该节点的孩子节点 */
        thisNode.child.clear();
        thisNode.child.push_back(simpleExpStmt(begin, iter));
        iter++;
        thisNode.child.push_back(simpleExpStmt(iter, end));
        // TODO: handle error
        return treeNode;
    }
}

/* 简单表达式语句 */
TreeNode * Parser::simpleExpStmt(std::list<CompTokenType>::iterator &begin, std::list<CompTokenType>::iterator end) {
    // TODO: handle error
    /* TermStmt匹配到的节点的末尾 */
    TreeNode * term = termStmt(begin);
    while (begin != end) {
        if (begin->type == ADD || begin->type == MINUS) {
            TreeNode * treeNode = new TreeNode;
            TreeNode & thisNode = * treeNode;
            /* 初始化节点信息 */
            thisNode.lineno = lineNumber;
            thisNode.nodeKind = EXPK;
            thisNode.expK = OPK;
            thisNode.op = begin->type;
            thisNode.child.clear();
            thisNode.child.push_back(term);
            begin++;
            TreeNode * termTmp = termStmt(begin);
            thisNode.child.push_back(termTmp);
            term = treeNode;
        } else {
            // TODO: handle error
            begin++;
            return NULL;
        }
    }
    // TODO: handle error
    return term;
}

/* 单项式语句 */
TreeNode * Parser::termStmt(std::list<CompTokenType>::iterator &begin) {
    // TODO: handle error
    TreeNode * factor = factorStmt(begin);
    while (begin != tokenList.end() && (begin->type == MUL || begin->type == DIV || begin->type == MOD)) {
        TreeNode * treeNode = new TreeNode;
        TreeNode & thisNode = * treeNode;
        /* 初始化节点信息 */
        thisNode.lineno = lineNumber;
        thisNode.nodeKind = EXPK;
        thisNode.expK = OPK;
        thisNode.op = begin->type;
        thisNode.child.clear();
        thisNode.child.push_back(factor);
        begin++;
        thisNode.child.push_back(factorStmt(begin));
        factor = treeNode;
    }
    // TODO: handle error
    return factor;
}

