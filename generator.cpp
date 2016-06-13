//
//  generator.cpp
//  java_complier
//
//  Created by noprom on 6/11/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "generator.h"

/* 多个语句 */
void Generator::mulGen(TreeNode *syntaxTree) {
    while (syntaxTree != NULL) {
        sentenceGen(syntaxTree);
        syntaxTree = syntaxTree->sibling;
    }
}

/* 单个语句 */
void Generator::sentenceGen(TreeNode *syntaxTree) {
    if (syntaxTree->nodeKind != STMTK) {
        // TODO: handle error
        return;
    }
    switch (syntaxTree->stmtKind) {
        case ASSIGNK:
            assignGen(syntaxTree);
            break;
        case WHILEK:
            whileGen(syntaxTree);
            break;
        default:
            // TODO: handle error
            break;
    }
}

/* while语句 */
void Generator::whileGen(TreeNode *syntaxTree) {
    
}

/* 赋值语句 */
void Generator::assignGen(TreeNode *syntaxTree) {
    
}

/* 表达式语句 */
void Generator::expGen(TreeNode *syntaxTree) {
    
}