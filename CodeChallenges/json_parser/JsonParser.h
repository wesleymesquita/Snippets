//
// Created by wesley on 8/9/24.
//

#ifndef SNIPPETS_JSONPARSER_H
#define SNIPPETS_JSONPARSER_H

#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>

enum class TokenType {
    START_OBJECT,
    END_OBJECT,
    START_ARRAY,
    END_ARRAY,
    WHITESPACE,
    STRING,
    NUMBER,
    TRUE,
    FALSE,
    NULL_,
    COMMA,
    COLON,
    NONE,
    INVALID
};

static inline std::map<TokenType, std::string> TOKEN_TYPE_STR =
        {
                {TokenType::START_OBJECT, "START_OBJECT"},
                {TokenType::END_OBJECT,   "END_OBJECT"},
                {TokenType::START_ARRAY,  "START_ARRAY"},
                {TokenType::END_ARRAY,    "END_ARRAY"},
                {TokenType::WHITESPACE,   "WHITESPACE"},
                {TokenType::TRUE,         "TRUE"},
                {TokenType::FALSE,        "FALSE"},
                {TokenType::NULL_,        "NULL"},
                {TokenType::STRING,       "STRING"},
                {TokenType::NUMBER,       "NUMBER"},
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

class NumberToken : public Token {
public:
    NumberToken(const std::string &&val, size_t position);

    std::string value;
};


class JsonParser {
public:
    explicit JsonParser(const std::string &file_path);

    bool is_valid() const;


    using TokenRef = std::unique_ptr<Token>;

private:

    inline static const std::vector<char> TRUE{'t', 'r', 'u', 'e'};
    inline static const std::vector<char> FALSE{'f', 'a', 'l', 's', 'e'};
    inline static const std::vector<char> NULL_{'n', 'u', 'l', 'l'};
    inline static const std::string STR{"string"};
    inline static const std::string NUMBER{"number"};

    std::ifstream file;
    std::string file_path;
    char buf[1];
    bool eof;
    size_t position;
    bool valid;

    bool open();

    bool parse();

    char read_next();

    char get_current();

    bool is_eof();

    bool parse_fixed(const std::vector<char> &fixed_val);

    bool parse_false();

    bool parse_true();

    bool parse_null();

    std::vector<char> temp_bytes;

    bool parse_sequence(bool (*char_checker)(char c), const std::string &error);

    bool parse_string();

    bool parse_number();

};

class Grammar {
public:
    static inline std::map<TokenType, std::set<TokenType>> RULES =
            {{TokenType::NONE,         {TokenType::START_OBJECT}},
             {TokenType::START_OBJECT, {TokenType::STRING,       TokenType::END_OBJECT}},
             {TokenType::STRING,       {TokenType::COLON,        TokenType::COMMA,       TokenType::END_OBJECT}},
             {TokenType::NUMBER,       {TokenType::COLON,        TokenType::COMMA,       TokenType::END_OBJECT}},
             {TokenType::TRUE,         {TokenType::COMMA,        TokenType::END_OBJECT,  TokenType::END_ARRAY}},
             {TokenType::FALSE,        {TokenType::COMMA,        TokenType::END_OBJECT,  TokenType::END_ARRAY}},
             {TokenType::NULL_,        {TokenType::COMMA,        TokenType::END_OBJECT,  TokenType::END_ARRAY}},
             {TokenType::END_OBJECT,   {TokenType::COMMA}},
             {TokenType::COMMA,        {TokenType::START_OBJECT, TokenType::START_ARRAY, TokenType::STRING, TokenType::NUMBER, TokenType::TRUE,  TokenType::FALSE, TokenType::NULL_}},
             {TokenType::COLON,        {TokenType::STRING,       TokenType::NUMBER,      TokenType::TRUE,   TokenType::FALSE,  TokenType::NULL_}},
             {TokenType::START_ARRAY,  {TokenType::END_ARRAY,    TokenType::STRING,      TokenType::NUMBER, TokenType::TRUE,   TokenType::FALSE, TokenType::NULL_}},
             {TokenType::END_ARRAY,    {TokenType::END_OBJECT,   TokenType::COMMA}}
            };

    static bool parse(const std::vector<JsonParser::TokenRef> &tokens);
};

#endif //SNIPPETS_JSONPARSER_H
