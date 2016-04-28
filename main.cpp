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
int TraceScan = 1;

int main(int argc, const char * argv[]) {
    
    if (argc != 2) {
        std::cout << "Usage: lexer <filename>" << std::endl;
        exit(1);
    }
    std::string fileName = argv[1];
    
    /* 开始词法分析 */
    if (NO_PARSE) {
        Lexer lexer = Lexer(fileName);
        TokenType token = lexer.getToken();
        while (token != ENDFILE) {
            token = lexer.getToken();
        }
    }
    return 0;
}