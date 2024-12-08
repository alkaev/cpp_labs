#include <cstring>

#include "FileWorker.hpp"


namespace HuffmanArchiver {


Buffer::
Buffer(const std::vector<uint8_t> str, std::size_t len): str(str), len(len) {}

Buffer::
Buffer(std::size_t len, uint8_t value): len(len) {
    str = std::vector<uint8_t> (len, value);
}

std::size_t Buffer::
get_len() const {
    return len;
}

const std::vector<uint8_t>& Buffer::
get_data() const {
    return str;
}

uint8_t& Buffer::
operator[] (std::size_t ind) {
    return str[ind];
}

const uint8_t Buffer::
operator[] (std::size_t ind) const {
    return str[ind];
}

bool Buffer::
operator < (const Buffer& other) const {
    if (this->len != other.len) {
        return this->len < other.len;
    }
    return this->str < other.str;
}

bool Buffer::
operator== (const Buffer& other) const {
    return !(other < *this) && !(*this < other);
}

bool Buffer::
operator!= (const Buffer& other) const {
    return !(*this == other);
}

Buffer& Buffer::
operator = (const Buffer& other) {
    
    if (this == &other)
        return *this;
    
    str.resize(other.str.size());
    std::copy(other.str.begin(), other.str.end(), str.begin());
    len = other.len;
    return *this;
}


Buffer& Buffer::
operator+=(const Buffer& other) {
    this->str.resize(len + other.len);
    for (std::size_t i = 0; i < other.len; ++i) {
        this->str[i + len] = other.str[i];
    }
    this->len += other.len;
    return *this;
}

Buffer Buffer::
operator+(const Buffer& other) {
    Buffer res(*this);
    return res += other;
}


void Buffer::
reverse() {
    for (std::size_t i = 0; i * 2 < str.size(); ++i) {
        std::swap(str[i], str[str.size() - i - 1]);
    }
}

void Buffer::
print() const {
    for (uint8_t val: str) {
        printf("%d", val);
    }
}

Writer::
Writer(std::ofstream& out): out(out), buffer(0), buf_size(0) {}

void Writer::
write(const Buffer &buf) {
    for (auto val: buf.get_data()) {
        buffer += (val << buf_size);
        buf_size++;
        if (buf_size == 8) {
            out.write((char*)&buffer, 1);
            buffer = 0;
            buf_size = 0;
        }
    }
}

Reader::
Reader(std::ifstream& in): in(in), buffer(0), buf_size(0) {}

std::size_t Reader::
get_buf_size() {
    return buf_size;
}

void Reader::
read(Buffer& buf) {
    for (std::size_t i = 0; i < buf.get_len(); i++) {
        if (buf_size == 0) {
            buf_size = 8;
            buffer = 0;
            in.read((char*)&buffer, 1);
        }
        buf[i] = (buffer >> (8 - buf_size)) % 2;
        buf_size--;
    }
}

}