//
//  main.cpp
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "globals.h"

/* NO_PARSE 为1则只是一个词法分析器 */
#define NO_PARSE 0

#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "generator.h"

/* 输出扫描结果 */
int TraceScan = 0;
int TraceSource = 0;

int main(int argc, const char * argv[]) {

    /* 输入的分析文件名称 */
	std::string fileName;
    /* 词法分析器扫描结果文件 */
	std::string outFileName = "scanner_output.txt";
    /* 中间代码生成文件 */
    std::string codeFileName = "tuple4_code.txt";

	std::cout << "Please input a filename:" << std::endl;
	std::cin >> fileName;

    if (NO_PARSE) {
        Lexer::runLexer(fileName, outFileName);
    } else {
        /* 开始语法分析 */
        Parser parser = Parser(fileName);
        TreeNode * syntaxTree = parser.parse();
        
        /* 生成四元式 */
        Generator::runGenerator(syntaxTree, fileName, codeFileName);
    }
	return 0;
}