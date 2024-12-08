#pragma once

#include <cstddef>
#include <fstream>
#include <string>

#include "HuffmanTreeNode.hpp"
#include "HuffmanTree.hpp"
#include "FileWorker.hpp"

namespace HuffmanArchiver {

enum TypeWork {Archivate, UnArchivate, NoType};

class HuffmanTreeArchiver {
    TypeWork type;
    std::map <char, Buffer> codes;
    std::map <char, std::uint64_t> frequency;
    std::uint64_t offset;
    std::int32_t cnt_char;
    std::uint32_t mem_inp;
    std::uint32_t mem_out;
    std::uint32_t mem_add;
public:
    HuffmanTreeArchiver();
    void fit(std::ifstream& in, TypeWork type);
    void transform(std::ifstream& in, std::ofstream& out);
    void archive(std::ifstream& in, std::ofstream& out);
    void unarchive(std::ifstream& in, std::ofstream& out);
    std::uint32_t get_mem_out() const;
    std::uint32_t get_mem_inp() const;
    std::uint32_t get_mem_add() const;
};

}