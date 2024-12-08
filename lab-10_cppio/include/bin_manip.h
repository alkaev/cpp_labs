#ifndef BIN_MANIP_H
#define BIN_MANIP_H

#include <iostream>
#include <cstdint>

namespace manip
{

    class write_le_int32
    {
    private:
        std::int32_t _x;

    public:
        explicit write_le_int32(std::int32_t x);
        friend std::ostream &operator<<(std::ostream &os, const write_le_int32 &value);
    };

    class read_le_int32
    {
    private:
        std::int32_t *_x;

    public:
        explicit read_le_int32(std::int32_t &x);
        friend std::istream &operator>>(std::istream &is, const read_le_int32 &value);
    };

    class write_bool
    {
    private:
        bool _x;

    public:
        explicit write_bool(bool x);
        friend std::ostream &operator<<(std::ostream &os, const write_bool &value);
    };

    class read_bool
    {
    private:
        bool *_x;

    public:
        explicit read_bool(bool &x);
        friend std::istream &operator>>(std::istream &is, const read_bool &value);
    };

    class write_c_str
    {
    private:
        char _s[101];

    public:
        explicit write_c_str(const char *s);
        friend std::ostream &operator<<(std::ostream &os, const write_c_str &value);
    };

    class read_c_str
    {
    private:
        char *_s;
        size_t _size;

    public:
        read_c_str(char *s, size_t size);
        friend std::istream &operator>>(std::istream &is, const read_c_str &value);
    };
}

#endif 
