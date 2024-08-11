//
// Created by wesley on 8/9/24.
//
#include "JsonParser.h"
#include <string>
#include <iostream>

int main(int argc, char** argv){

    std::string file_name;

    if(argc == 2) {
        file_name = std::string{argv[1]};
    }else{
        file_name = std::string{"/dev/stdin"};
    }
    try {
        JsonParser parser(file_name);
        if(!parser.is_valid()){
            return 1;
        }
    }catch(const std::string& error){
        std::cerr << "Exception: " << error << std::endl;
        return 1;
    }
    return 0;
}