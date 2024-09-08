//
// Created by wesley on 9/8/24.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

#include "Cut.h"

bool Cut::_exec(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << ERROR_INVALID_ARGUMENTS << std::endl;
        return false;
    }

    std::vector<const Option *> options;

    for (int i = 1; i < argc; i++) {
        const char *option = _parse_option(argv[i]);
        if (strcmp(option, INVALID_OPTION) == 0) {
            // last argument. Can be the file
            if(i == argc -1) {

            }
            return false;
        }

        Option op = OPTIONS.at(option);
        op.set_args(argv[i]);
        options.push_back(&op);
    }


    return true;
}

const char *Cut::_parse_option(const char *option) {
    if (option == nullptr || strlen(option) == 0) {
        return INVALID_OPTION;
    }
    if (option[0] != '-') {
        return INVALID_OPTION;
    }

    if (option[1] != '-') {
        switch (option[1]) {
            case 'b':
                return BYTES;
            case 'c':
                return CHARACTERS;
            case 'd':
                return DELIMITERS;
            case 'f':
                return FIELDS;
            case 's':
                return ONLY_DELIMITED;
            case 'z':
                return ZERO_TERMINATED;
        }
    }

    if (strstr(option, COMPLEMENT)) {
        return COMPLEMENT;
    }

    if (strstr(option, OUTPUT_DELIMITER)) {
        return OUTPUT_DELIMITER;
    }

    if (strstr(option, HELP)) {
        return HELP;
    }

    if (strstr(option, VERSION)) {
        return VERSION;
    }

    return INVALID_OPTION;
}

bool Bytes::set_args(const char *carg) {
    std::string arg(carg + 2);

    if (arg.empty()) {
        return false;
    }

    std::stringstream from_arg(arg);
    std::stringstream num;
    this->n = -1;
    this->m = -1;

    char c;
    from_arg >> c;
    if (c == '-') {
        from_arg >> c;
        while (!from_arg.eof() && isdigit(c)) {
            num << c;
            from_arg >> c;
        }
        num >> this->n;
        this->m = 0;
    } else {
        from_arg >> c;
        while (!from_arg.eof() && isdigit(c)) {
            num << c;
            from_arg >> c;
        }
        num >> m;

        from_arg >> c;
        if (c == '-') {
            num.str("");
            while (!from_arg.eof() && isdigit(c)) {
                num << c;
                from_arg >> c;
            }
            num >> n;
        }
    }
    return true;
}

bool Bytes::exec(const std::string &line, std::string &result) {

    result.clear();
    if (this->m >= line.size() || this->n >= line.size()) {
        return false;
    }

    result = std::string(line.begin() + this->m, line.begin() + this->n);
    return true;
}



