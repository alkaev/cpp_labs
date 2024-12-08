#pragma once

#include <cstddef>
#include <set>
#include <map>
#include <string>

#include "HuffmanTreeNode.hpp"

namespace HuffmanArchiver {

enum HuffmanErrors{NotLeafError, ErrorFormatFile, EmpFrequencies};

class HuffmanTree {
private:
    int32_t root;
    std::vector<HuffmanTreeNode> _data;
public:
    HuffmanTree();
    void fit(const std::map<char, std::size_t> &frequencies);
    Buffer get_code(std::size_t pos) const;
};

}