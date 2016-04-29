//
//  main.cpp
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "globals.h"

/* 
 * NO_PARSE = TRUE
 * 则只是一个词法分析器
 */
#define NO_PARSE 1

#include "util.h"
#if NO_PARSE
#include "lexer.h"
#endif

/* 输出扫描结果 */
int TraceScan = 0;
int TraceSource = 0;

int main(int argc, const char * argv[]) {

    std::string fileName;
    if (argc != 2) {
        fileName = "./App.java";
//        std::cout << "Usage: lexer <filename>" << std::endl;
//        exit(1);
    } else {
        fileName = argv[1];
    }
    
    if (NO_PARSE) {
        /* 开始词法分析 */
        Lexer lexer = Lexer(fileName);
        TokenType token = lexer.getToken();
        while (token != ENDFILE) {
            token = lexer.getToken();
        }
        
        /* 输出统计结果 */
        printf("Total tokens: %d\n", lexer.TOKEN_NUM);
        for (std::map<int, int>::iterator it = lexer.lineTokenSumMap.begin();
             it != lexer.lineTokenSumMap.end(); ++it) {
            std::pair<int, int> pair = *it;
            printf("%5d:\t%5d\t tokens\n", pair.first, pair.second);
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
        }
    }
    return 0;
}