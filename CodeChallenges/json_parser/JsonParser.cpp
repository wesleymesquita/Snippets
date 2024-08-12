//
// Created by wesley on 8/9/24.
//

#include "JsonParser.h"
#include <iostream>

Token::Token(TokenType t) : type{t} {}

Token::Token() : type{TokenType::NONE} {}

StringToken::StringToken(const std::string &&val) :
        Token{TokenType::STRING},
        value{val} {}

bool Grammar::parse(const std::vector<Token> &tokens) {
    Token currToken{TokenType::NONE};
    for (const Token &token: tokens) {
        if (RULES.find(token.type) == RULES.end()) {
            std::cerr << "No mapping found for token " << TOKEN_TYPE_STR[token.type] << std::endl;
            return false;
        }
        if (RULES.find(currToken.type) != RULES.end()) {
            currToken = token;
        } else {
            std::cerr << "No rule found from " << TOKEN_TYPE_STR[currToken.type] << " to " << TOKEN_TYPE_STR[token.type]
                      << std::endl;
            return false;
        }
    }
    return true;
}


JsonParser::JsonParser(const std::string &file_path) : file_path{file_path}, eof{false} {

    if (!this->parse()) {
        throw std::string("File" + file_path + " is invalid");
    }
}

bool JsonParser::is_eof() {
    return this->eof;
}

bool JsonParser::open() {
    file.open(file_path);
    if (!file.is_open()) {
        std::cerr << "Could not open file " + file_path << std::endl;
        return false;
    }
    return true;
}

static bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

char JsonParser::read_next() {
    this->file.read(buf, 1);
    if (this->file.eof()) {
        this->eof = true;
        return 0;
    }
    this->eof = false;
    return buf[0];
}

bool JsonParser::parse() {
    bool is_open = this->open();
    if (!is_open) {
        return false;
    }
    std::vector<Token> tokens;
    Token last_token;
    char c = read_next();
    while (!is_eof()) {
        switch (c) {
            case '{':
                tokens.emplace_back(TokenType::START_OBJECT);
                break;
            case '}':
                tokens.emplace_back(TokenType::END_OBJECT);
                break;
            case ',':
                tokens.emplace_back(TokenType::COMMA);
                break;
            case ' ':
                tokens.emplace_back(TokenType::WHITESPACE);
                while (c == ' ' && !is_eof()) {
                    c = read_next();
                }
                continue;
            case '"':
                c = read_next();
                std::vector<char> letters;
                while (is_letter(c)) {
                    letters.push_back(c);
                    c = read_next();
                }
                if (c != '"') {
                    std::cerr << "Found invalid string " << std::endl;
                    return false;
                } else {
                    tokens.emplace_back(StringToken(std::string(letters.begin(), letters.end())));
                }
                break;
        }
        c = read_next();
    }
    return Grammar::parse(tokens);
}

bool JsonParser::is_valid() {
    Grammar grammar;

    return this->valid;
}
