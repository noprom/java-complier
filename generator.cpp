//
//  generator.cpp
//  java_complier
//
//  Created by noprom on 6/11/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "generator.h"

/* 构造函数 */
Generator::Generator() {
    /* 初始化成员变量 */
    number = 1;
    resultIndex = 1;
    lastResult = "LAST-RESLUT-LABEL";
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
            updateTuple4();
            break;
        default:
            // TODO: handle error
            break;
    }
}

/* while语句 */
void Generator::whileGen(TreeNode *syntaxTree) {
    /* 首先是括号之内的判断表达式 */
    expGen(syntaxTree->child[0]);
    /* 接着是判断结果之后的跳转, 看其是否跳转到while语句的下一条语句 */
    int backNo = number - 1;
    Tuple4 tuple = newTuple4(number++, "jT", result, "", int2str(number + 1), 0);
    tuple4List.push_back(tuple);
    tuple = newTuple4(number++, "j", "", "", lastResult, 0);
    tuple4List.push_back(tuple);
    
    /* 然后执行循环体 */
    assignGen(syntaxTree->child[1]);
    
    /* 最后是循环执行, 返回到条件判断部分 */
    tuple = newTuple4(number++, "j", "", "", int2str(backNo), backNo);
    tuple4List.push_back(tuple);
}

/* 赋值语句 */
void Generator::assignGen(TreeNode *syntaxTree) {
    /* 赋值语句 */
    Tuple4 tuple;
    if (syntaxTree != NULL && syntaxTree->child.size() > 0) {
        if (syntaxTree->child[0]->nodeKind == STMTK && syntaxTree->child[0]->stmtKind == ASSIGNK) {
            /* 首先执行等号右边的表达式 */
            expGen(syntaxTree->child[0]);
            /* 然后生成最后一个赋值语句 */
            Tuple4 tuple = newTuple4(number++, "=", "last exe val no in assign", "", syntaxTree->id, 0);
            tuple4List.push_back(tuple);
            /* 表达式 */
        } else if (syntaxTree->child[0]->nodeKind == EXPK) {
            /* 后面直接跟着数字或者标志符 */
            if (syntaxTree->child[0]->stmtKind == NUMK || syntaxTree->child[0]->stmtKind == IDK) {
                tuple = newTuple4(number++, "=", syntaxTree->child[0]->id, "", syntaxTree->id, 0);
                tuple4List.push_back(tuple);
                return;
            } else {
                expGen(syntaxTree->child[0]);
                /* 最后的赋值语句 */
                tuple = newTuple4(number++, "=", result, "", syntaxTree->id, 0);
                tuple4List.push_back(tuple);
            }
        }
    }
}

/* 表达式语句 */
void Generator::expGen(TreeNode *syntaxTree) {
    /* 操作符节点 */
    Tuple4 tuple;
    Lexer lexer;
    std::string arg1;
    std::string arg2;
    if (syntaxTree->expK == OPK) {
        /* 四元式中的第一个参数 */
        if (syntaxTree->child[0]->expK == NUMK || syntaxTree->child[0]->expK == IDK) {
            arg1 = syntaxTree->child[0]->id;
        } else {
            expGen(syntaxTree->child[0]);
            arg1 = result;
        }
        /* 四元式中的第二个参数 */
        if (syntaxTree->child[1]->expK == NUMK || syntaxTree->child[1]->expK == IDK) {
            arg2 = syntaxTree->child[1]->id;
        } else {
            expGen(syntaxTree->child[1]);
            arg2 = result;
        }
        switch (syntaxTree->op) {
            case EQU:
            case NE:
            case GT:
            case LT:
            case GE:
            case LE:
                /* 更新结果 */
                updateResultLabel(syntaxTree->op);
                /* 生成新的四元组 */
                tuple = newTuple4(number++, lexer.tokenMap[syntaxTree->op].first, arg1, arg2, result, 0);
                tuple4List.push_back(tuple);
                break;
            case ADD:
            case MINUS:
            case MUL:
            case DIV:
                updateResultLabel(syntaxTree->op);
                /* 生成新的四元组 */
                tuple = newTuple4(number++, lexer.tokenMap[syntaxTree->op].first, arg1, arg2, result, 0);
                tuple4List.push_back(tuple);
                break;
            default:
                break;
        }
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

/* 更新结果项的下标 */
void Generator::updateResultNumber(TokenType op) {
    if (op == ADD || op == MINUS || op == MUL || op == DIV ) {
        resultIndex++;
    }
}

/* 更新结果项 */
void Generator::updateResultLabel(TokenType op) {
    updateResultNumber(op);
    std::string res = "T";
    char str[10];
    sprintf(str, "%d", resultIndex);
    res += str;
    result = res;
}

/* 具有判断性质的语句执行完成之后
 * 更新跳转到下一条语句的标号 */
void Generator::updateTuple4() {
    for (std::vector<Tuple4>::iterator it = tuple4List.begin(); it != tuple4List.end(); it++) {
        Tuple4 item = *it;
        if (item.result == lastResult) {
            it->result = int2str(number);
        }
    }
}

/* 运行代码生成器 */
void Generator::runGenerator(TreeNode * syntaxTree, std::string codeFile) {
    Generator generator = Generator();
    generator.codeGen(syntaxTree);
    /* 输出到文件 */
    FILE *fp = fopen(codeFile.c_str(), "w");
    
    /* 打印出四元式列表 */
    printf("NO  %2s %4s %4s %4s\n", "OP", "ARG1", "ARG2", "RESULT");
    fprintf(fp, "NO  %2s %4s %4s %4s\n", "OP", "ARG1", "ARG2", "RESULT");
    for (std::vector<Tuple4>::iterator it = generator.tuple4List.begin(); it != generator.tuple4List.end(); it++) {
        Tuple4 item = *it;
        printf("%2d:(%2s,%4s,%4s,%4s)\n", item.no, item.op.c_str(), item.arg1.c_str(), item.arg2.c_str(), item.result.c_str());
        fprintf(fp, "%2d:(%2s,%4s,%4s,%4s)\n", item.no, item.op.c_str(), item.arg1.c_str(), item.arg2.c_str(), item.result.c_str());
    }
    /* 下一条语句 */
    printf("%2d:...\n", generator.number);
    fprintf(fp, "%2d:...\n", generator.number);
    fclose(fp);
}