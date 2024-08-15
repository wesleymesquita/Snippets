//
// Created by wesley on 8/14/24.
//

#include "gtest/gtest.h"
#include "JsonParser.h"

TEST(JsonParserTest, BasicAssertions){
    JsonParser parser("../tests/1.txt");
    EXPECT_EQ(parser.is_valid(), true);
}