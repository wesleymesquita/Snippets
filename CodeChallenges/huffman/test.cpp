//
// Created by wesley on 8/24/24.
//

#include "Huffman.h"
#include "gtest/gtest.h"

TEST(HuffmanFrequencyTable, BasicAssertions) {
    Huffman huff;
    EXPECT_EQ(huff.compress("../data/135-0.txt", "../data/1.txt"), true);
    EXPECT_EQ(huff.get_frequency('X'), 333);
    EXPECT_EQ(huff.get_frequency('t'), 223000);
}

TEST(HuffmanCompress, BasicAssertions ) {
    Huffman huff;
    EXPECT_EQ(huff.compress("../data/135-0.txt", "../data/1.txt"), true);
}
