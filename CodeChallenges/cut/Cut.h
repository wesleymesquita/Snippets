//
// Created by wesley on 9/8/24.
//

#ifndef RANDOMWALK_CUT_H
#define RANDOMWALK_CUT_H

#include <fstream>
#include <string>
#include <map>


class Option {
public:
    virtual bool exec(const std::string &line, std::string &result);

    virtual bool set_args(const char *arg);
};

class Bytes : public Option {
public:
    Bytes();

    bool exec(const std::string &line, std::string &result) override;

    bool set_args(const char *arg) override;

    int m, n; // interval from m(inclusive) to n(inclusive)
};

class Characters : public Option {
public:
    Characters();
};

class Delimiter : public Option {
public:
    Delimiter();
};

class Fields : public Option {
public:
    Fields();
};

class Complement : public Option {
public:
    Complement();
};

class OnlyDelimited : public Option {
public:
    OnlyDelimited();
};

class OutputDelimiter : public Option {
public:
    OutputDelimiter();
};

class ZeroTerminated : public Option {
public:
    ZeroTerminated();
};

class Help : public Option {
public:
    Help();
};

class Version : public Option {
public:
    Version();
};

class Invalid : public Option {
public:
    Invalid();
};

class Cut {
public:
    Cut(int argc, char **argv);

private:
    static const inline char *INVALID_OPTION = {"__INVALID__"};
    static const inline char *BYTES = {"-b"};
    static const inline char *CHARACTERS = {"-c"};
    static const inline char *DELIMITERS = {"-d"};
    static const inline char *FIELDS = {"-f"};
    static const inline char *COMPLEMENT = {"--complement"};
    static const inline char *ONLY_DELIMITED = {"-s"};
    static const inline char *OUTPUT_DELIMITER = {"--output-delimiter"};
    static const inline char *ZERO_TERMINATED = {"-z"};
    static const inline char *HELP = {"--help"};
    static const inline char *VERSION = {"--version"};

    static const inline std::map<const char *, Option> OPTIONS =
            {
                    {BYTES,            Bytes()},
                    {CHARACTERS,       Characters()},
                    {DELIMITERS,       Delimiter()},
                    {FIELDS,           Fields()},
                    {COMPLEMENT,       Complement()},
                    {ONLY_DELIMITED,   OnlyDelimited()},
                    {OUTPUT_DELIMITER, OutputDelimiter()},
                    {ZERO_TERMINATED,  ZeroTerminated()},
                    {HELP,             Help()},
                    {VERSION,          Version()},
                    {INVALID_OPTION,   Invalid()}
            };

    static const char *_parse_option(const char *arg);

    static const inline std::string ERROR_INVALID_ARGUMENTS = {
            "cut: you must specify a list of bytes, characters, or fields"};
    static const inline std::string NO_SUCH_FILE = { "No such file or directory"};
    static const inline std::string TRY_HELP = {"Try 'cut --help' for more information."};

    std::vector<std::ifstream> input_files;

    bool _exec(int argc, char *argv[]);

};

#endif //RANDOMWALK_CUT_H
