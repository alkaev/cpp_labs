#include <cstddef>
#include <set>
#include <map>
#include <string>



#include "HuffmanTreeArchiver.hpp"

namespace HuffmanArchiver {

/* 

format:

cnt_char: std::int32_t
i from 0 upto cnt_char:
    char[i]: std::int8_t,
    frequencies[i]: std::uint64_t
*archivated file*

*/

HuffmanTreeArchiver::
HuffmanTreeArchiver() {
    type = TypeWork::NoType;
    offset = 0;
    cnt_char = 0;
    mem_inp = 0;
    mem_out = 0;
    mem_add = 0;
    codes = std::map <char, Buffer>();
    frequency = std::map <char, std::uint64_t>();
}

void HuffmanTreeArchiver::
fit(std::ifstream& in, TypeWork type) 
{
    this->type = type;
    if (type == TypeWork::Archivate)
    {
        char sym;
        in.read(&sym, 1);

        while(!in.eof()) {
            ++frequency[sym];   
            in.read(&sym, 1);
        }

        in.clear();
        in.seekg(0, in.beg);
    }
    else 
    {
        in.read((char*)&cnt_char, 4);
        char sym;
        std::uint64_t cnt;
        for (std::int32_t i = 0; i < cnt_char; ++i) {
            in.read((char*)&sym, 1);
            in.read((char*)&cnt, 8);
            frequency[sym] = cnt;
        }
    }

    if (frequency.size() == 0)
        return;
    
    HuffmanTree tree;
    tree.fit(frequency);

    std::uint64_t ind = 0;
    std::uint64_t total_len = 0;

    char sym;
    mem_inp = 0;
    for (auto sym_freq: frequency) {
        mem_inp += sym_freq.second;
        sym = sym_freq.first;
        Buffer code = tree.get_code(ind);
        codes[sym] = code;
        ++ind;
        total_len += sym_freq.second * code.get_len();
    }

    offset = (8 - total_len % 8) % 8;
}

void HuffmanTreeArchiver::
transform(std::ifstream& in, std::ofstream& out) {
    if (type == TypeWork::Archivate) 
        archive(in, out);
    else 
        unarchive(in, out);
}

void HuffmanTreeArchiver::
archive(std::ifstream& in, std::ofstream& out) {
    Writer writer(out);
    std::uint64_t cnt = frequency.size();
    if (cnt == 0)
        return;

    out.write((const char*)&cnt, 4);
    mem_add += 4;
    for (auto sym_freq: frequency) 
    {
        mem_add += 9;
        out.write(&sym_freq.first, 1);
        out.write((const char*)&sym_freq.second, 8);
    }

    in.clear();
    in.seekg(0, in.beg);

    char sym;
    in.read(&sym, 1);
    while(! in.eof()) {
        mem_out += codes[sym].get_len();
        writer.write(codes[sym]);
        in.read(&sym, 1);
    }
    mem_out = (mem_out + 7) / 8;
    writer.write(Buffer(offset, 0)); // Zeroes in the last byte
}

void HuffmanTreeArchiver::
unarchive(std::ifstream& in, std::ofstream& out) {
    std::map<Buffer, char> values;
    if (frequency.size() == 0) 
        return;
    
    for (auto code: this->codes) 
        values[code.second] = code.first;

    Reader reader(in);
    Buffer buf(1, 0), new_code(0, 0);

    mem_add = in.tellg();
    in.seekg(0, std::ios::end);
    std::uint64_t file_size = in.tellg() * 8 - 1;
    mem_inp = uint32_t(in.tellg()) - mem_add;
    in.clear();        
    in.seekg(mem_add, in.beg);

    if (mem_inp == 0) {
        mem_add = 0;
        mem_out = 0;
        return;
    }

    while (file_size >= mem_add * 8 + offset) {
        reader.read(buf);
        new_code += buf;
        file_size -= 1;
        
        if (values.count(new_code)) {
            out << values[new_code];
            mem_out += 1;
            new_code = Buffer(0, 0);
        }
    }

    if (new_code.get_len() != 0)
        throw HuffmanErrors::ErrorFormatFile;
}

std::uint32_t  HuffmanTreeArchiver::
get_mem_out() const {
    return mem_out;
}

std::uint32_t  HuffmanTreeArchiver::
get_mem_inp() const {
    return mem_inp;
}

std::uint32_t  HuffmanTreeArchiver::
get_mem_add() const {
    return mem_add;
}
}