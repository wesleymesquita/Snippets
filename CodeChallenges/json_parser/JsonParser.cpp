//
// Created by wesley on 8/9/24.
//

#include "JsonParser.h"
#include <iostream>

Token::Token(TokenType type, size_t position) : type{type}, position{position} {}

StringToken::StringToken(const std::string &&val, size_t position) :
        Token{TokenType::STRING, position},
        value{val} {}

NumberToken::NumberToken(const std::string &&val, size_t position) :
        Token{TokenType::NUMBER, position},
        value{val} {}

bool Grammar::parse(const std::vector<JsonParser::TokenRef> &tokens) {
    if (tokens.size() == 0) {
        return false;
    }
    TokenType currToken{TokenType::NONE};
    for (const JsonParser::TokenRef &token: tokens) {

        if (token->type == TokenType::INVALID) {
            std::cerr << "Invalid token at position " << token->position << std::endl;
            return false;
        }

        if (token->type == TokenType::WHITESPACE) {
            continue;
        }
        if (RULES.find(token->type) == RULES.end()) {
            std::cerr << "No mapping found for token " << TOKEN_TYPE_STR[token->type] << std::endl;
            return false;
        }
        if (RULES.find(currToken) != RULES.end()) {
            currToken = token->type;
        } else {
            std::cerr << "No rule found from " << TOKEN_TYPE_STR[currToken] << " to " << TOKEN_TYPE_STR[token->type]
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

char JsonParser::read_next() {
    this->file.read(buf, 1);
    this->position++;
    if (this->file.eof()) {
        this->eof = true;
        buf[0] = 0;
        return buf[0];
    }
    this->eof = false;
    return buf[0];
}

char JsonParser::get_current(){
    return buf[0];
}

bool JsonParser::parse() {
    bool is_open = this->open();
    if (!is_open) {
        return false;
    }
    std::vector<TokenRef> tokens;
    char c{read_next()};
    while (!is_eof()) {
        switch (c) {
            case '{':
                tokens.emplace_back(new Token{TokenType::START_OBJECT, position});
                break;
            case '}':
                tokens.emplace_back(new Token{TokenType::END_OBJECT, position});
                break;
            case ',':
                tokens.emplace_back(new Token{TokenType::COMMA, position});
                break;
            case ':':
                tokens.emplace_back(new Token{TokenType::COLON, position});
                break;
            case ' ':
                tokens.emplace_back(new Token{TokenType::WHITESPACE, position});
                while (c == ' ' && !is_eof()) {
                    c = read_next();
                }
                continue;
            case '"': {
                if(parse_string()) {
                    std::string s{temp_bytes.begin(), temp_bytes.end()};
                    tokens.emplace_back(new StringToken {std::move(s), position});
                }else{
                    return false;
                }
                break;
            }
            case '[': {
                tokens.emplace_back(new Token{TokenType::START_ARRAY, position});
                break;
            }
            case ']': {
                tokens.emplace_back(new Token{TokenType::END_ARRAY, position});
                break;
            }
            case 'f':
                 if (parse_false()) {
                    tokens.emplace_back(new Token{TokenType::FALSE, position});
                } else {
                    return false;
                }
                break;
            case 't':
                if (parse_true()) {
                    tokens.emplace_back(new Token{TokenType::TRUE, position});
                } else {
                    return false;
                }
                break;
            case 'n':
                if (parse_null()) {
                    tokens.emplace_back(new Token{TokenType::NULL_, position});
                } else {
                    return false;
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if(parse_number()) {
                    std::string s{temp_bytes.begin(), temp_bytes.end()};
                    tokens.emplace_back(new NumberToken {std::move(s), position});
                }else{
                    return false;
                }
                break;

            default:
                tokens.emplace_back(new Token{TokenType::INVALID, position});
        }
        c = read_next();
    }
    return Grammar::parse(tokens);
}

bool JsonParser::parse_sequence(bool (*char_checker)(char c), const std::string& type_chars){
    char c;
    temp_bytes.clear();

    c = read_next();
    while (char_checker(c)) {
        temp_bytes.push_back(c);
        c = read_next();
    }
    if (c != '"') {
        std::cerr << "Error: Found invalid " << type_chars << "position " << position << std::endl;
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

bool JsonParser::parse_string() {
    return parse_sequence(is_letter, STR);
}

bool JsonParser::parse_number() {
    return parse_sequence(is_digit, NUMBER);
}

bool JsonParser::parse_fixed(const std::vector<char>& fixed_val) {
    char c{get_current()};

    size_t pos{0};

    for (; pos < fixed_val.size(); pos++) {
        if (c != fixed_val[pos] || is_eof()) {
            break;
        }
        c = read_next();
    }
    if (pos != fixed_val.size()) {
        return false;
    }
    return true;
}

bool JsonParser::parse_false() {
    if (parse_fixed(FALSE)) {
        return true;
    }
    std::cerr << "Error: Expected 'false' at position " << this->position << std::endl;
    return false;
}

bool JsonParser::parse_true() {
    if (parse_fixed(TRUE)) {
        return true;
    }
    std::cerr << "Error: Expected 'true' at position " << this->position << std::endl;
    return false;
}

bool JsonParser::parse_null() {
    if (parse_fixed(NULL_)) {
        return true;
    }
    std::cerr << "Error: Expected 'null' at position " << this->position << std::endl;
    return false;
}

bool JsonParser::is_valid() const {
    return this->valid;
}
