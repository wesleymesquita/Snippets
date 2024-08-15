//
// Created by wesley on 8/14/24.
//

#include <sstream>
#include <map>
#include <iostream>

#include "gtest/gtest.h"
#include "JsonParser.h"

TEST(JsonParserTest, BasicAssertions) {
    bool test_specific{false};

    const std::string prefix{"../tests/"};
    std::map<int, bool> expected{
            {1, true},
            {2, false},
            {3, false},
            {4, true},
            {5, true}
    };

    std::map<int, bool> expected_specific{
            {1, true},
    };

    if(test_specific) {
        expected = expected_specific;
    }

    for(auto& entry : expected){
        std::stringstream ss;
        ss << prefix;
        ss << entry.first;
        ss << ".txt";
        JsonParser parser(ss.str());
        std::cout << "Testing " << ss.str() << " which is " << (parser.is_valid() ? "":" not") << " valid" << std::endl;
        EXPECT_EQ(parser.is_valid(), entry.second);
    }
}