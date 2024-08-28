//
// Created by wesley on 8/24/24.
//

#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <bitset>

#include <iostream>

#include "Huffman.h"

Huffman::Huffman() : buf{new char[BUF_SIZE]}, tree_root{nullptr} {}

Huffman::~Huffman() {
    if (this->tree_root != nullptr) {
        std::stack<TreeNode *> nodes;
        nodes.push(this->tree_root);
        TreeNode *curr{nullptr};
        while (!nodes.empty()) {
            curr = nodes.top();
            nodes.pop();
            if(curr->right != nullptr){
                nodes.push(curr->right);
            }
            if(curr->left != nullptr){
                nodes.push(curr->left);
            }
            delete curr;
        }
    }

    delete [] buf;
}

size_t Huffman::get_frequency(char c) {
    if (this->frequency_table.find(c) == this->frequency_table.end()) {
        return 0;
    }
    return this->frequency_table[c];
}

bool Huffman::compress(const std::string &from_file_path, const std::string &to_file_path) {
    std::ifstream fin{from_file_path};
    std::ofstream fout{to_file_path, std::fstream::binary};

    if (!fin.is_open()) {
        std::cerr << "COMPRESS: Could not open file " << from_file_path << " for reading " << std::endl;
        return false;
    }

    if (!fout.is_open()) {
        std::cerr << "COMPRESS: Could not open file " << to_file_path << " for writing " << std::endl;
        return false;
    }

    if (!_build_frequency_table(fin)) {
        std::cerr << "COMPRESS: Could not build frequency table " << std::endl;
        return false;
    }

    if (!_build_tree()) {
        std::cerr << "COMPRESS: Could not build huffman tree " << std::endl;
        return false;
    }

    // get back to beg of file and read each character
    // for compression process
    fin.clear();
    fin.seekg(0);

    std::streamsize rd_size = fin.readsome(buf, BUF_SIZE);
    std::vector<bool> output;
    while (rd_size > 0) {
        for (std::streamsize i = 0; i < rd_size; i++) {
            unsigned char c = buf[i];
            std::vector<bool> &path = huff_map[c];
            output.insert(output.end(), path.begin(), path.end());
        }
        rd_size = fin.readsome(buf, BUF_SIZE);
    }

    if(!_dump_frequency_table(fout)) {
        std::cerr << "COMPRESS: Could not write frequency table to compressed file" << std::endl;
        return false;
    }

    constexpr size_t BIT_BUFFER_SIZE{sizeof(signed long long) * 8};

    size_t bit_stream_sz = output.size();
    fout.write(reinterpret_cast<char *>(&bit_stream_sz), sizeof(size_t));

    std::bitset<BIT_BUFFER_SIZE> bit_buffer;
    bit_buffer.reset();
    size_t bit_buf_idx{0};

    for (size_t i = 0; i < bit_stream_sz; i++) {
        if (bit_buf_idx < BIT_BUFFER_SIZE) {
            bit_buffer.set(bit_buf_idx++, output[i]);
        } else {
            unsigned long long v = bit_buffer.to_ullong();
            fout.write(reinterpret_cast<char *>(&v), sizeof(unsigned long long));
            bit_buffer.reset();
            bit_buf_idx = 0;
        }
    }

    if (bit_buf_idx > 0) {
        unsigned long long v = bit_buffer.to_ullong();
        fout.write(reinterpret_cast<char *>(&v), sizeof(unsigned long long));
    }

    fout.close();
    return true;
}

bool Huffman::decompress(const std::string &from_file_path, const std::string &to_file_path) {

    std::ifstream fin{from_file_path, std::fstream::binary};
    std::ofstream fout{to_file_path};

    if (!fin.is_open()) {
        std::cerr << "DECOMPRESS: Could not open file " << from_file_path << " for reading " << std::endl;
        return false;
    }

    if (!fout.is_open()) {
        std::cerr << "DECOMPRESS: Could not open file " << to_file_path << " for writing" << std::endl;
        return false;
    }

    if (!_load_frequency_table(fin)) {
        std::cerr << "DECOMPRESS: Could not load frequency table for decompressing " << std::endl;
        return false;
    }

    this->huff_map.clear();

    _build_tree();

    constexpr size_t BIT_BUFFER_SIZE{sizeof(unsigned long long) * 8};
    TreeNode *curr{this->tree_root};

    size_t bit_stream_sz;
    fin.read(reinterpret_cast<char *>(&bit_stream_sz), sizeof(size_t));
    size_t bit_i{0};

    unsigned long long path;
    fin.read(reinterpret_cast<char *>(&path), sizeof(unsigned long long));
    std::bitset<BIT_BUFFER_SIZE> bit_buffer(path);
    size_t bit_buffer_i{0};

    while (bit_i <= bit_stream_sz) {

        if (curr->is_leaf) {
            fout.write(reinterpret_cast<char*>(&curr->data), sizeof(unsigned char));
            curr = this->tree_root;
        }

        if (bit_buffer.test(bit_buffer_i)) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }

        if (bit_buffer_i == BIT_BUFFER_SIZE-1) {
            fin.read(reinterpret_cast<char *>(&path), sizeof(unsigned long long));
            bit_buffer = std::bitset<BIT_BUFFER_SIZE>(path);
            bit_buffer_i = 0;
        } else {
            bit_buffer_i++;
        }

        bit_i++;
    }

    return true;
}

static void add_to_table(std::map<unsigned char, size_t> &table, char c) {
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

Huffman::TreeNode::TreeNode(unsigned char datum, size_t freq) : data{datum}, freq{freq}, is_leaf{true}, left{nullptr},
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

bool Huffman::_visit_tree(TreeNode* root, std::vector<bool> &path, std::map<unsigned char, std::vector<bool>> &huff_map) {

    if(root != nullptr) {
        if(root->is_leaf) {
            huff_map[root->data] = path;
        }

        if(root->right != nullptr) {
            path.push_back(true);
            _visit_tree(root->right, path, huff_map);
        }

        if(root->left != nullptr){
            path.push_back(false);
            _visit_tree(root->left, path, huff_map);
        }
        path.erase(path.end());
    }

    return true;
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

    this->tree_root = pq.top();

    pq.pop();

    std::vector<bool> path;
    huff_map.clear();
    _visit_tree(this->tree_root, path, huff_map);

    return true;
}

bool Huffman::_dump_frequency_table(std::ofstream &fout) {
    if (this->frequency_table.empty()) {
        return false;
    }
    size_t table_size{this->frequency_table.size()};
    fout.write(reinterpret_cast<char *>(&table_size), sizeof(size_t));

    for (auto &pair: this->frequency_table) {
        fout.write(reinterpret_cast<const char *>(&pair.first), sizeof(char));
        fout.write(reinterpret_cast<char *>(&pair.second), sizeof(size_t));
    }

    return true;
}

bool Huffman::_load_frequency_table(std::ifstream &fin) {
    if (!fin.is_open()) {
        return false;
    }

    if (!this->frequency_table.empty()) {
        this->frequency_table.clear();
    }

    size_t table_size;
    fin.read(reinterpret_cast<char *>(&table_size), sizeof(size_t));

    if (table_size == 0) {
        return false;
    }

    char c;
    size_t freq;
    for (int i = 0; i < table_size; i++) {
        fin.read(reinterpret_cast<char *>(&c), sizeof(char));
        fin.read(reinterpret_cast<char *>(&freq), sizeof(size_t));
        this->frequency_table[c] = freq;
    }

    return true;
}
