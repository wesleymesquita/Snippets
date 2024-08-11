//
// Created by wesley on 8/9/24.
//

#ifndef SNIPPETS_JSONPARSER_H
#define SNIPPETS_JSONPARSER_H

#include <fstream>
#include <vector>
#include <map>
#include <set>

enum class TokenType {
    START_OBJECT,
    END_OBJECT,
    WHITESPACE,
    STRING,
    NONE
};

static inline std::map<TokenType, std::string> TOKEN_TYPE_STR =
        {
                {TokenType::START_OBJECT, "START_OBJECT"},
                {TokenType::END_OBJECT,   "END_OBJECT"},
                {TokenType::WHITESPACE,   "WHITESPACE"},
                {TokenType::STRING,       "STRING"},
                {TokenType::NONE,         "NONE"},
        };

class Token {
public:
    Token(TokenType type);

    Token();

    TokenType type;
};

class StringToken : public Token {
public:
    StringToken(const std::string &&val);

    std::string value;
};

class Grammar {
public:
    static inline std::map<TokenType, std::set<TokenType>> RULES =
            {
                    {TokenType::NONE,         {TokenType::WHITESPACE, TokenType::START_OBJECT}},
                    {TokenType::START_OBJECT, {TokenType::WHITESPACE, TokenType::END_OBJECT}}
            };

    static bool parse(const std::vector<Token> &tokens);
};


class Element {
public:
    std::vector<Element> elements;
};


class JsonParser {
public:
    JsonParser(const std::string &file_path);

    bool is_valid();
    char read_next();
    bool is_eof();
private:
    std::ifstream file;
    std::string file_path;
    char buf[1];
    bool eof;

    bool valid;

    bool parse();

    bool open();
};


#endif //SNIPPETS_JSONPARSER_H
