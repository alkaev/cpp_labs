#pragma once

#include <fstream>
#include <string>
#include <cstddef>
#include <vector>


#include <iostream>


namespace HuffmanArchiver {

class Buffer {
    std::vector<uint8_t> str;
    std::uint64_t len;
public:
    Buffer(const std::vector<uint8_t> str , std::uint64_t len);
    Buffer(std::uint64_t len = 0, uint8_t value = 0);
    std::uint64_t get_len() const;
    const std::vector<uint8_t>&  get_data() const;
    const uint8_t operator[](std::uint64_t ind) const;
    uint8_t& operator[](std::uint64_t ind);

    bool operator < (const Buffer& other) const;
    bool operator == (const Buffer& other) const;
    bool operator != (const Buffer& other) const;
    Buffer& operator += (const Buffer& other);
    Buffer operator + (const Buffer& other);
    Buffer& operator =(const Buffer& other);

    void reverse();

    void print() const;
};

class Writer {
    std::ofstream& out;
    uint16_t buffer;
    std::uint64_t buf_size;
public:
    Writer(std::ofstream& out);
    void write(const Buffer& buf); 
};

class Reader {
    std::ifstream& in;
    uint16_t buffer;
    std::uint64_t buf_size;
public:
    Reader(std::ifstream& in);
    std::uint64_t get_buf_size();
    void read(Buffer& buf); 
};
}