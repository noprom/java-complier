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
        /* 开始词法分析 */
        Lexer lexer = Lexer(fileName);
        TokenType token = lexer.getToken();
        while (token != ENDFILE) {
            token = lexer.getToken();
        }
        
        /* 输出到文件 */
        FILE *fp = fopen(outFileName.c_str(), "w");
        
        /* 输出统计结果 */
        printf("Total tokens: %d\n", lexer.TOKEN_NUM);
        fprintf(fp, "Total tokens: %d\n", lexer.TOKEN_NUM);
        for (std::map<int, int>::iterator it = lexer.lineTokenSumMap.begin();
             it != lexer.lineTokenSumMap.end(); ++it) {
            std::pair<int, int> pair = *it;
            if (pair.second > 1) {
                printf("%5d:%5d\t tokens\n", pair.first, pair.second);
                fprintf(fp, "%5d:%5d\t tokens\n", pair.first, pair.second);
            }
            else {
                printf("%5d:%5d\t token\n", pair.first, pair.second);
                fprintf(fp, "%5d:%5d\t token\n", pair.first, pair.second);
            }
        }
        
        /* 输出提示字符串 */
        printf("\n\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("+                      Scan Result                  +\n");
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("\n\n");
        
        /* 输出扫描结果 */
        for (std::vector<Token>::iterator it = lexer.tokenList.begin();
             it != lexer.tokenList.end(); ++it) {
            Token token = *it;
            printf("%4d: %15s \t %15s \t %10s\n", token.lineNumber, token.value.c_str(), token.typeName.c_str(), token.attr.c_str());
            fprintf(fp, "%4d: %15s \t %15s \t %10s\n", token.lineNumber, token.value.c_str(), token.typeName.c_str(), token.attr.c_str());
        }
        
        /* 输出错误信息列表 */
        for (std::vector<TokenErrorInfo>::iterator it = lexer.errList.begin();
             it != lexer.errList.end(); ++it) {
            TokenErrorInfo err = *it;
            printf("Error line: %4d, %s", err.lineNumber, err.lineBuf.c_str());
            printf("Error position: %d, error token: %s\n", err.errorPos, err.errorToken.c_str());
            fprintf(fp, "Error line: %4d, %s", err.lineNumber, err.lineBuf.c_str());
            fprintf(fp, "Error position: %d, error token: %s\n", err.errorPos, err.errorToken.c_str());
        }
        
        fclose(fp);
    } else {
        /* 开始语法分析 */
        TreeNode * syntaxTree;
        Parser parser = Parser(fileName);
        syntaxTree = parser.parse();
        // TODO 语义分析
        /* 生成汇编代码 */
    }
	return 0;
};

