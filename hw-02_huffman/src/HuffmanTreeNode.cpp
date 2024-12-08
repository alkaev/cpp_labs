#include <algorithm>

#include "HuffmanTreeNode.hpp"


namespace HuffmanArchiver {

HuffmanTreeNode::
HuffmanTreeNode(
        int32_t left, 
        int32_t right,
        int32_t head,
        std::size_t freq,
        char sym,
        uint32_t ind
):  head(head), left(left), right(right), ind(ind), freq(freq), sym(sym) {}

int32_t HuffmanTreeNode::
get_left() const {
    return left;
}

int32_t HuffmanTreeNode::
get_right() const {
    return right;
}

int32_t HuffmanTreeNode::
get_head() const {
    return head;
}

std::size_t HuffmanTreeNode::
get_freq() const {
    return freq;
}

char HuffmanTreeNode::
get_sym() const {
    return sym;
}

void HuffmanTreeNode::
set_left(uint32_t left) {
    this->left = left;
}

void HuffmanTreeNode::
set_right(uint32_t right) {
    this->right = right;
}

void HuffmanTreeNode::
set_head(uint32_t head) {
    this->head = head;
}

void HuffmanTreeNode::
set_freq(std::size_t freq) {
    this->freq = freq;
}

void HuffmanTreeNode::
set_sym(char sym) {
    this->sym = sym;
}

}