//
//  lexer.h
//  java_complier
//
//  Created by noprom on 4/27/16.
//  Copyright © 2016 tyee.noprom@qq.com. All rights reserved.
//

#ifndef _LEXER_H
#define _LEXER_H

#include "globals.h"
#include "util.h"

/* DFA的状态 */
typedef enum {
    /**
     * 开始, 结束, 读入标志符, 读入字符常量, 读入字符串常量, 读入数字, 读入浮点型, 读入转义符号, 读入界限符, 读入注释
     * 读入+ - * / % & = < > | ! ^
     */
    START, DONE, IN_ID, IN_CONST_CHAR, IN_CONST_STR, IN_NUM, IN_FLOAT, IN_ESC, IN_DELIMETER, IN_COMMENT,
    IN_ADD, IN_MINUS, IN_MUL, IN_DIV, IN_MOD, IN_AND, IN_ASSIGN, IN_LT, IN_GT, IN_OR, IN_NOT, IN_XOR
    
} DFAStateType;

/* Token的信息 */
typedef struct {
    /* token所在行号 */
    int lineNumber;
    /* token类型名称 */
    std::string typeName;
    /* token类型 */
    TokenType type;
    /* token的值 */
    std::string value;
    /* token属性字 */
    std::string attr;
} Token;

/* 词法分析器类 */
class Lexer {
    
public:
    /* 词法分析阶段程序错误标志 */
    static int LEXER_ERROR;
    
    /* EOF结束标志 */
    static int EOF_flag;
    
    /* 总单词个数 */
    static int TOKEN_NUM;
    
    /* 每行单词个数统计 */
    std::map<int, int> lineTokenSumMap;
    
    /* 扫描出的所有单词 */
    std::vector<Token> tokenList;

    /**
     * 构造函数
     *
     * @fileName 文件名
     */
    Lexer(std::string fileName);
    
    /**
     * 析构函数
     * 释放某些成员变量
     */
//    ~Lexer();
    
    /**
     * 获得单词的token
     *
     * @return token状态
     */
    virtual TokenType getToken();
    
protected:
    /* 扫描到的行数 */
    static int lineNumber;
    
    /* 扫描到某行的位置 */
    static int linePos;
    
    /* 每行单词的个数 */
    static int lineTokenNum;
    
    /* 提取出来的单词 */
    static std::string tokenString;
    
    /* 单词属性及其对应Token的关系 */
    std::map<TokenType, std::pair<std::string, std::string> > tokenMap;
private:
    /* 输入文件流 */
    std::ifstream ifstream;
    
    /* 输出文件流 */
    std::ofstream ofstream;
    
    /* 读入的每一行字符流 */
    std::string lineBuf;
    
    /* DFA的状态 */
    DFAStateType currentState;
    
    /* 关键字及其对应Token的关系 */
    std::map<std::string, std::pair<TokenType, std::string> > keyWords;
    
    /* 界限符与对应Token的关系 */
    std::map<char, TokenType> delimeterMap;
    
    /**
     * 读取一行内容并存入lineBuf
     * @return void
     */
    void getOneLine();
    
    /**
     * 获得下一个字符
     *
     * @return 下一个字符
     */
    char getNextChar();
    
    /**
     * 回退一个字符
     *
     * @return void
     */
    void ungetNextChar();
    
    /**
     * 扫描错误
     *
     * @return void
     */
    void scanError();
    
    /**
     * 打印token的信息
     *
     * @param token token类型
     * @param tokenString token 保存字符串
     */
    void printToken(TokenType token, std::string tokenString);
    
    /**
     * 创建一个token
     * 
     * @param type token类型
     * @param tokenString token 保存的字符串
     * @return 新的token
     */
    Token createToken(TokenType type, std::string tokenString);
    
    /**
     * 获得一个token的类型名称
     *
     * @param type token 类型
     * @param tokenString token的值
     */
    std::string getTokenTypeName(TokenType type, std::string tokenString);
};
#endif
