#include <cstring>

#include "HuffmanTreeNode.hpp"
#include "HuffmanTree.hpp"



namespace HuffmanArchiver {

HuffmanTree::
HuffmanTree() {
    root = -1;
    _data = std::vector<HuffmanTreeNode>(0);
}

void HuffmanTree::
fit(const std::map<char, std::uint64_t> &frequencies) {
    if (frequencies.size() == 0) {
        throw HuffmanErrors::EmpFrequencies;
    }
    _data = std::vector<HuffmanTreeNode>(frequencies.size() * 2);

    std::multimap<std::uint64_t, uint32_t> freq_nodes;
    uint32_t last_free = 0;

    for (auto freq: frequencies) {
        _data[last_free].set_freq(freq.second);
        _data[last_free].set_sym(freq.first);

        freq_nodes.insert({freq.second, last_free});
        ++last_free;
    }

    while (freq_nodes.size() > 1) {
        auto first_node = freq_nodes.begin(); 
        _data[last_free].set_left(first_node->second); 

        _data[first_node->second].set_head(last_free);
        uint64_t new_freq = first_node->first;

        freq_nodes.erase(freq_nodes.begin());

        auto second_node = freq_nodes.begin();

        new_freq += second_node->first;
        _data[last_free].set_right(second_node->second);
        _data[last_free].set_freq(new_freq);

        _data[second_node->second].set_head(last_free);
        freq_nodes.erase(freq_nodes.begin());
        freq_nodes.insert({new_freq, last_free});
        ++last_free;
    }

    root = freq_nodes.begin()->second;
}

Buffer HuffmanTree::
get_code(std::uint64_t pos) const {
    int32_t local_node = pos;
    Buffer buf(0, 0);

    if (_data[local_node].get_left() != -1 || _data[local_node].get_right() != -1) 
        throw HuffmanErrors::NotLeafError;

    if (local_node == root) 
        return Buffer(1, 0);
    
    while (local_node != root) {
        auto head = _data[local_node].get_head();
        if (_data[head].get_right() == local_node) {
            buf = buf + Buffer(1, 1);
        }
        else {
            buf = buf + Buffer(1, 0);
        }
        local_node = head;
    }

    buf.reverse();
    return buf;
}

}