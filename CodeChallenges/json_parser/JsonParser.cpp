//
// Created by wesley on 8/9/24.
//

#include "JsonParser.h"
#include <iostream>

Token::Token(TokenType type, size_t position) : type{type}, position{position} {}

StringToken::StringToken(const std::string &&val, size_t position) :
        Token{TokenType::STRING, position},
        value{val} {}

bool Grammar::parse(const std::vector<Token> &tokens) {
    Token currToken{TokenType::NONE, 0};
    for (const Token &token: tokens) {

        if (token.type == TokenType::INVALID) {
            std::cerr << "Invalid token at position " << token.position << std::endl;
            return false;
        }

        if (token.type == TokenType::WHITESPACE) {
            continue;
        }
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


JsonParser::JsonParser(const std::string &file_path) : file_path{file_path}, eof{false}, position{0} {
    this->valid = this->parse();
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

static bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

size_t JsonParser::read_next(char &c) {
    this->file.read(buf, 1);
    position++;
    if (this->file.eof()) {
        this->eof = true;
        c = 0;
        return position;
    }
    this->eof = false;
    c = buf[0];
    return  position;
}

bool JsonParser::parse() {
    bool is_open = this->open();
    if (!is_open) {
        return false;
    }
    std::vector<Token> tokens;
    size_t position{0};
    char c;
    position = read_next(c);
    while (!is_eof()) {
        switch (c) {
            case '{':
                tokens.emplace_back(Token{TokenType::START_OBJECT, position});
                break;
            case '}':
                tokens.emplace_back(Token{TokenType::END_OBJECT, position});
                break;
            case ',':
                tokens.emplace_back(Token{TokenType::COMMA, position});
                break;
            case ':':
                tokens.emplace_back(Token{TokenType::COLON, position});
                break;
            case ' ':
                tokens.emplace_back(Token{TokenType::WHITESPACE, position});
                while (c == ' ' && !is_eof()) {
                    position = read_next(c);
                }
                continue;
            case '"': {
                position = read_next(c);
                std::vector<char> letters;
                while (is_letter(c)) {
                    letters.push_back(c);
                    position = read_next(c);
                }
                if (c != '"') {
                    std::cerr << "Found invalid string " << std::endl;
                    return false;
                } else {
                    tokens.emplace_back(StringToken(std::string(letters.begin(), letters.end()), position));
                }
                break;
            }
            default:
                tokens.emplace_back(Token{TokenType::INVALID, position});
        }
        position = read_next(c);
    }
    return Grammar::parse(tokens);
}

bool JsonParser::is_valid() {
    return this->valid;
}
