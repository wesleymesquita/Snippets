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
    Huffman compressor;
    EXPECT_EQ(compressor.compress("../data/test1.txt", "../data/compressed_test1.txt"), true);
    Huffman decompressor;
    EXPECT_EQ(decompressor.decompress("../data/compressed_test1.txt", "../data/decompressed_test1.txt"), true);
}

TEST(HuffmanCompressStr, BasicAssertions ) {
    Huffman huff;
    EXPECT_EQ(huff.compress_str("AAABBB"), "");
}
