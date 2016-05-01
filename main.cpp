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
    
    std::string fileName = "/Users/noprom/Documents/Dev/C++/Complier/java_complier/java_complier/App.java";
    std::string outFileName = "/Users/noprom/Documents/Dev/C++/Complier/java_complier/java_complier/scanner_output.txt";
    
    if (argc > 2) {
        fileName = argv[1];
        outFileName = argv[2];
    } else {
//        std::cout << "Usage: lexer <input filename> <output filename>" << std::endl;
//        exit(1);
    }
    
    if (NO_PARSE) {
        /* 开始词法分析 */
        Lexer lexer = Lexer(fileName);
        TokenType token = lexer.getToken();
        while (token != ENDFILE) {
            token = lexer.getToken();
        }
        /* 关闭文件 */
        lexer.ifstream.close();
        
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
            } else {
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
            fprintf(fp, "%4d: %s", err.lineNumber, err.lineBuf.c_str());
            fprintf(fp, "\t: Error position: %d, error token: %s\n", err.errorPos, err.errorToken.c_str());
        }
        
        fclose(fp);
    }
    return 0;
}