//
// Created by wesley on 8/24/24.
//

#ifndef JSONPARSER_HUFFMAN_H
#define JSONPARSER_HUFFMAN_H

#include <string>
#include <map>
#include <fstream>
#include <memory>
#include <vector>

class Huffman {
public:
    Huffman();

    ~Huffman();

    size_t get_frequency(char c);

    bool compress(const std::string &from_file_path, const std::string &to_file_path);

    bool decompress(const std::string &from_file_path, const std::string &to_file_path);

private:
    static const inline size_t BUF_SIZE{1024};

    typedef struct TreeNode {
        TreeNode(char data, size_t freq);

        TreeNode(TreeNode *left, TreeNode *right);

        bool operator<(TreeNode *other) const;

        char data;
        size_t freq;
        bool is_leaf;
        TreeNode *right, *left;
    } TreeNode;


    char *buf;
    std::map<char, size_t> frequency_table;
    std::map<char, std::vector<bool>> huff_map;
    TreeNode *tree_root;

    bool _build_frequency_table(std::ifstream &file);

    bool _build_frequency_table(const std::string &content);

    bool _build_tree();

    bool _visit_tree(Huffman::TreeNode* root, std::vector<bool> &path, std::map<char, std::vector<bool>> &huff_map);

    bool _dump_frequency_table(std::ofstream &fout);

    bool _load_frequency_table(std::ifstream &fout);
};


#endif //JSONPARSER_HUFFMAN_H
