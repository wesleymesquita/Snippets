//
// Created by wesley on 8/7/24.
//

#include <fstream>
#include <cstring>
#include <iostream>

enum class Error {
    INVALID_OPTION = 1,
    FILE_NOT_OPEN = 2
};

void print_invalid_option(const char *program_name, const char *invalid_option) {
    std::cerr << program_name << ": invalid option -- " << invalid_option << std::endl;
}

void print_file_not_open(const char *program_name, const char *file_name) {
    std::cerr << program_name << ": " << file_name << " No such file or directory" << std::endl;
}


enum class Option {
    COUNT_BYTES,
    COUNT_LINES,
    COUNT_WORDS,
    COUNT_CHARS,
    NONE,
    INVALID
};

enum class Source {
    FROM_FILE,
    FROM_STDIN
};

Option get_action(const char *op) {
    if (op == nullptr) {
        return Option::INVALID;
    }
    if (strcmp(op, "-c") == 0) {
        return Option::COUNT_BYTES;
    }
    if (strcmp(op, "-l") == 0) {
        return Option::COUNT_LINES;
    }
    if (strcmp(op, "-w") == 0) {
        return Option::COUNT_WORDS;
    }
    if (strcmp(op, "-m") == 0) {
        return Option::COUNT_CHARS;
    }
    return Option::INVALID;
}

size_t count_words(const std::string &line) {
    if (line.size() == 0) {
        return 0;
    }
    size_t count{0};
    size_t s = line.size();
    size_t i{0};
    while (line[i] == ' ') {
        i++;
    }

    for (; i < s; i++) {
        if (line[i] == ' ' || line[i] == 9 || line[i] == '\n') {
            count++;
        }
    }
    return count + 1;
}


int main(int argc, char **argv) {
    Option option = Option::NONE;
    Source source = Source::FROM_STDIN;
    std::ifstream file;

    if (argc == 3) {
        option = get_action(argv[1]);
        if (option == Option::INVALID) {
            print_invalid_option(argv[0], argv[1]);
            return static_cast<int>(Error::INVALID_OPTION);
        }
        file.open(argv[2]);
        if (!file.is_open()) {
            print_file_not_open(argv[0], argv[2]);
            return static_cast<int>(Error::FILE_NOT_OPEN);
        }
    } else if (argc == 2) {
        option = get_action(argv[1]);
        std::string file_name;
        if(option != Option::INVALID) {
           file_name = "/dev/stdin";
        }else{
            file_name = argv[1];
        }
        file.open(file_name);
        if (!file.is_open()) {
            print_file_not_open(argv[0], file_name.c_str());
            return static_cast<int>(Error::FILE_NOT_OPEN);
        }
    }else{
        file.open("/dev/stdin");
        option = Option::NONE;
    }
    std::string line;
    int line_count{0}, char_count{0}, word_count{0}, byte_count{0};
    while (std::getline(file, line)) {
        line_count++;
        word_count += count_words(line);
        byte_count += (line.size() + 1); // +1 to get line feed
        char_count = byte_count;
    }

    switch (option) {
        case Option::COUNT_CHARS:
            std::cout << char_count << " " << argv[2] << std::endl;
            break;
        case Option::COUNT_BYTES:
            std::cout << byte_count << " " << argv[2] << std::endl;
            break;
        case Option::COUNT_LINES:
            std::cout << line_count << " " << argv[2] << std::endl;
            break;
        case Option::COUNT_WORDS:
            std::cout << word_count << " " << argv[2] << std::endl;
            break;
        case Option::NONE:
            std::cout << ' ' << line_count << ' ' << word_count << ' ' << char_count << ' ' << argv[1] << std::endl;
            break;
        case Option::INVALID:
            std::cerr << "Must not have INVALID here....";
    }
    return 0;
}
