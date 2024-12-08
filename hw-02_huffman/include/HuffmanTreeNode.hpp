#pragma once   

#include "FileWorker.hpp"

#include <algorithm>
#include <cstddef>

namespace HuffmanArchiver {

class HuffmanTreeNode {
    int32_t head, left, right;
    uint32_t ind;
    std::uint64_t freq;
    char sym;
public:
    HuffmanTreeNode(
        int32_t left = -1, 
        int32_t right = -1,
        int32_t head = -1, 
        std::uint64_t freq = 0,
        char sym = 0,
        uint32_t ind = 0
        );

    int32_t get_left() const;
    int32_t get_right() const;
    int32_t get_head() const;
    std::uint64_t get_freq() const;
    char get_sym() const;

    void set_left(uint32_t left);
    void set_right(uint32_t right);
    void set_head(uint32_t head);
    void set_freq(std::uint64_t freq);
    void set_sym(char sym);
};

}