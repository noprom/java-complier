//
//  util.cpp
//  java_complier
//
//  Created by noprom on 4/28/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#include "util.h"
//#include "lexer.h"

/* 判断否个字符是否是标识符 */
bool isIdentifier(char c) {
    if (isalpha(c) || c == '_' || c == '$') {
        return true;
    }
    return false;
}

///* 打印token的信息 */
//void printToken(TokenType token, std::string tokenString) {
//    std::string tokenName = Lexer::tokenMap[token].first;
//    std::string tokenVal = Lexer::tokenMap[token].second;
//    fprintf(stdout, "%s\t%s\t%s\n", tokenName.c_str(), tokenVal.c_str(), tokenString.c_str());
//}