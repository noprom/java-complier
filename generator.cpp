//
//  generator.cpp
//  java_complier
//
//  Created by noprom on 6/11/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "generator.h"

/* 构造函数 */
Generator::Generator() {
    /* 初始化成员变量 */
    number = 0;
    tuple4List.clear();
}

/* 生成四元式中间代码 */
void Generator::codeGen(TreeNode *syntaxTree) {
    mulGen(syntaxTree);
}

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
    /* 首先是括号之内的判断表达式 */
    expGen(syntaxTree);
    /* 接着是判断结果之后的跳转, 看其是否跳转到while语句的下一条语句 */
    int backNo = number;
    Tuple4 tuple = newTuple4(number++, "JF", "last exp val no", "", "next sentence no", 0);
    tuple4List.push_back(tuple);
    /* 最后是循环执行, 返回到条件判断部分 */
    tuple = newTuple4(number++, "", "", "", "", backNo);
    tuple4List.push_back(tuple);
}

/* 赋值语句 */
void Generator::assignGen(TreeNode *syntaxTree) {
    /* 赋值语句 */
    if (syntaxTree->child[0]->nodeKind == STMTK && syntaxTree->child[0]->stmtKind == ASSIGNK) {
        /* 首先执行等号右边的表达式 */
        expGen(syntaxTree->child[0]);
        /* 然后生成最后一个赋值语句 */
        Tuple4 tuple = newTuple4(number++, "=", "last exe val no in assign", "", syntaxTree->id, 0);
        tuple4List.push_back(tuple);
    /* 表达式 */
    } else if (syntaxTree->child[0]->nodeKind == EXPK) {
        expGen(syntaxTree->child[0]);
    }
}

/* 表达式语句 */
void Generator::expGen(TreeNode *syntaxTree) {
    /* 操作符节点 */
    Tuple4 tuple;
    std::string arg1;
    std::string arg2;
    if (syntaxTree->expK == OPK) {
        switch (syntaxTree->op) {
            case ADD:
            case MINUS:
                /* 运算符优先级, 先考虑第一个孩子节点的优先级别是否大于该节点 */
                if (syntaxTree->child[1]->expK == OPK &&
                    (syntaxTree->child[1]->op == MUL || syntaxTree->child[1]->op == DIV || syntaxTree->child[1]->op == MOD)) {
                    expGen(syntaxTree->child[1]);
                }
            case MUL:
            case DIV:
                /* 四元式中的第一个参数 */
                if (syntaxTree->child[0]->expK == NUMK) {
                    arg1 = syntaxTree->child[0]->num;
                } else if (syntaxTree->child[0]->expK == IDK) {
                    arg1 = syntaxTree->child[0]->id;
                } else {
                    expGen(syntaxTree->child[0]);
                }
                /* 四元式中的第二个参数 */
                if (syntaxTree->child[1]->expK == NUMK) {
                    arg2 = syntaxTree->child[1]->num;
                } else if (syntaxTree->child[1]->expK == IDK) {
                    arg2 = syntaxTree->child[1]->id;
                } else {
                    expGen(syntaxTree->child[1]);
                }

                /* 生成新的四元组 */
                tuple = newTuple4(number++, Lexer::tokenMap[syntaxTree->op].first, arg1, arg2, "op number", 0);
                tuple4List.push_back(tuple);
                break;
            default:
                // TODO: handle error
                break;
        }
    /* 变量名节点 */
    } else if (syntaxTree->expK == IDK) {
    /* 整数的值 */
    } else if (syntaxTree->expK == NUMK) {
    } else {
        // TODO: handle error
    }
}

/* 创建一个四元组 */
Tuple4 Generator::newTuple4(int no, std::string op, std::string arg1, std::string arg2, std::string result, int backNo) {
    Tuple4 * tuple4 = new Tuple4;
    tuple4->no = no;
    tuple4->op = op;
    tuple4->arg1 = arg1;
    tuple4->arg2 = arg2;
    tuple4->result = result;
    tuple4->backNo = backNo;
    return *tuple4;
}