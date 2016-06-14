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

	std::string fileName;
	std::string outFileName = "scanner_output.txt";
    std::string asmFileName = "asm_code.txt";

	std::cout << "Please input a filename:" << std::endl;
	std::cin >> fileName;

    if (NO_PARSE) {
        Lexer::runLexer(fileName, outFileName);
    } else {
        /* 开始语法分析 */
        TreeNode * syntaxTree;
        Parser parser = Parser(fileName);
        syntaxTree = parser.parse();
        // TODO 语义分析
        /* 生成四元式 */
        Generator generator = Generator();
        generator.codeGen(syntaxTree);
        /* 打印出四元式列表 */
        // printf("NO\tOP\tARG1\tARG2\tRESULT\n");
        for (std::vector<Tuple4>::iterator it = generator.tuple4List.begin(); it != generator.tuple4List.end(); it++) {
            Tuple4 item = *it;
            printf("%2d:(%2s,%4s,%4s,%4s)\n", item.no, item.op.c_str(), item.arg1.c_str(), item.arg2.c_str(), item.result.c_str());
        }
        /* 下一条语句 */
        printf("%2d:...\n", generator.number);
    }
	return 0;
}