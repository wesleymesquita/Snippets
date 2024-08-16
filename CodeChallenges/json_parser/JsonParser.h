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
    COMMA,
    COLON,
    NONE,
    INVALID
};
enum class ValueType {
    STRING,
    NUMBER,
    OBJECT,
    ARRAY,
    TRUE,
    FALSE,
    NULL
};

static inline std::map<TokenType, std::string> TOKEN_TYPE_STR =
        {
                {TokenType::START_OBJECT, "START_OBJECT"},
                {TokenType::END_OBJECT,   "END_OBJECT"},
                {TokenType::WHITESPACE,   "WHITESPACE"},
                {TokenType::STRING,       "STRING"},
                {TokenType::NONE,         "NONE"},
                {TokenType::COMMA,        "COMMA"},
                {TokenType::COLON,        "COLON"},
                {TokenType::INVALID,      "INVALID"},
        };

class Token {
public:
    Token(TokenType type, size_t position);
    TokenType type;
    size_t position;
};

class StringToken : public Token {
public:
    StringToken(const std::string &&val, size_t position);
    std::string value;
};

class ValueToken : public Token {
public:
ValueType valueType;
};

class Grammar {
public:
    static inline std::map<TokenType, std::set<TokenType>> RULES =
            {
                    {TokenType::NONE,         {TokenType::START_OBJECT}},
                    {TokenType::START_OBJECT, {TokenType::STRING, TokenType::END_OBJECT}},
                    {TokenType::STRING,       {TokenType::COLON,  TokenType::END_OBJECT}},
                    {TokenType::END_OBJECT,   {TokenType::COMMA}},
                    {TokenType::COMMA,        {TokenType::START_OBJECT}},
                    {TokenType::COLON,        {TokenType::STRING}}

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

    size_t read_next(char &c);

    bool is_eof();

private:
    std::ifstream file;
    std::string file_path;
    char buf[1];
    bool eof;
    size_t position;
    bool valid;

    bool parse();

    bool open();
};


#endif //SNIPPETS_JSONPARSER_H
