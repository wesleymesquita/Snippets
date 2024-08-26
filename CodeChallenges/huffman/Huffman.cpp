//
// Created by wesley on 8/24/24.
//

#include <string>
#include <fstream>
#include <queue>
#include <memory>
#include <stack>

#include "Huffman.h"

Huffman::Huffman() : buf{new char[BUF_SIZE]} {

}

std::string Huffman::compress_str(const std::string &content) {
    if (!this->_build_frequency_table(content)) {
        return "";
    }
    return "";
}

std::string Huffman::decompress_str(const std::string &content) {
    this->_build_frequency_table(content);
    return "";
}

size_t Huffman::get_frequency(char c) {
    if (this->frequency_table.find(c) == this->frequency_table.end()) {
        return 0;
    }
    return this->frequency_table[c];
}

static bool open_files(const std::string &from_file_path, std::ifstream &fin, const std::string &to_file_path,
                       std::ofstream &fout) {
    fin.open(from_file_path);
    if (!fin.is_open()) {
        return false;
    }
    fout.open(to_file_path, std::fstream::out);
    if (!fout.is_open()) {
        return false;
    }

    return true;
}

bool Huffman::compress(const std::string &from_file_path, const std::string &to_file_path) {
    std::ifstream fin;
    std::ofstream fout;
    if (!open_files(from_file_path, fin, to_file_path, fout)) {
        return false;
    }

    if (!_build_frequency_table(fin)) {
        return false;
    }

    if (!_build_tree()) {
        return false;
    }

    fin.clear();
    fin.seekg(0);

    std::streamsize rd_size = fin.readsome(buf, BUF_SIZE);
    std::vector<bool> output;
    while (rd_size > 0) {
        for (std::streamsize i = 0; i < rd_size; i++) {
            char c = buf[i];
            std::vector<bool> &path = huff_map[c];
            output.insert(output.end(), path.begin(), path.end());
        }
        rd_size = fin.readsome(buf, BUF_SIZE);
    }

    return true;
}

bool Huffman::decompress(const std::string &from_file_path, const std::string &to_file_path) {

    std::ifstream fin;
    std::ofstream fout;
    if (!open_files(from_file_path, fin, to_file_path, fout)) {
        return false;
    }

    return true;
}

static void add_to_table(std::map<char, int> &table, char c) {
    if (table.find(c) == table.end()) {
        table[c] = 1;
    } else {
        table[c]++;
    }
}

bool Huffman::_build_frequency_table(const std::string &content) {
    this->frequency_table.clear();
    for (char c: content) {
        add_to_table(this->frequency_table, c);
    }
    if (this->frequency_table.empty()) {
        return false;
    }
    return true;
}

bool Huffman::_build_frequency_table(std::ifstream &file) {
    if (!file.is_open()) {
        return false;
    }
    this->frequency_table.clear();
    std::streamsize sz = file.readsome(buf, BUF_SIZE);
    while (sz > 0) {
        for (int i = 0; i < sz; i++) {
            add_to_table(this->frequency_table, buf[i]);
        }
        sz = file.readsome(buf, BUF_SIZE);
    }

    if (this->frequency_table.empty()) {
        return false;
    }

    return true;
}

Huffman::TreeNode::TreeNode(char datum, size_t freq) : data{datum}, freq{freq}, is_leaf{true}, left{nullptr},
                                                       right{nullptr} {
}


Huffman::TreeNode::TreeNode(TreeNode *left, TreeNode *right) : data{128}, is_leaf{false} {
    this->freq = left->freq + right->freq;
    this->left = left;
    this->right = right;
}

bool Huffman::TreeNode::operator<(Huffman::TreeNode *other) const {
    return this->freq < other->freq;
}

bool Huffman::_build_tree() {
    if (this->frequency_table.empty()) {
        return false;
    }

    std::priority_queue<TreeNode *, std::vector<TreeNode *>,
            decltype([](TreeNode *left, TreeNode *right) { return left->freq > right->freq; })> pq;

    for (auto &pair: this->frequency_table) {
        pq.push(new Huffman::TreeNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        TreeNode *left = pq.top();
        pq.pop();
        TreeNode *right = pq.top();
        pq.pop();
        pq.push(new TreeNode{left, right});
    }

    std::stack<TreeNode *> visit;
    std::vector<bool> path;

    visit.push(pq.top());

    huff_map.clear();
    while (!visit.empty()) {
        TreeNode *root = visit.top();
        visit.pop();
        if (root->left != nullptr) {
            path.push_back(false);
            if (root->left->is_leaf) {
                huff_map[root->left->data] = path;
                path.erase(path.end());
            } else {
                visit.push(root->left);
            }
        }
        if (root->right != nullptr) {
            path.push_back(true);
            if (root->right->is_leaf) {
                huff_map[root->right->data] = path;
                path.erase(path.end());
            } else {
                visit.push(root->right);
            }
        }
    }

    return true;
}


