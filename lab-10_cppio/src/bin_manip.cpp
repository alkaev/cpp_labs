#include "bin_manip.h"
#include <cstring>

namespace manip
{
    write_le_int32::write_le_int32(std::int32_t x) : _x(x) {}

    std::ostream &operator<<(std::ostream &os, const write_le_int32 &manip)
    {
        std::uint32_t value = static_cast<std::uint32_t>(manip._x);
        for (int i = 0; i < 4; ++i)
        {
            os.put(static_cast<char>(value & 0xFF));
            value >>= 8;
        }
        return os;
    }

    read_le_int32::read_le_int32(std::int32_t &x) : _x(&x) {}

    std::istream &operator>>(std::istream &is, const read_le_int32 &manip)
    {
        std::uint32_t value = 0;
        for (int i = 0; i < 4; i++)
        {
            char byte;
            if (!is.get(byte)) return is;
            value |= (static_cast<std::uint32_t>(byte) & 0xFF) << (8 * i);
        }
        *(manip._x) = static_cast<std::int32_t>(value);
        return is;
    }

    write_bool::write_bool(bool x) : _x(x) {}

    std::ostream &operator<<(std::ostream &os, const write_bool &manip)
    {
        os.put(static_cast<char>(manip._x ? 1 : 0));
        return os;
    }

    read_bool::read_bool(bool &x) : _x(&x) {}

    std::istream &operator>>(std::istream &is, const read_bool &manip)
    {
        char byte;
        if (!is.get(byte)) return is;
        *(manip._x) = (byte != 0);
        return is;
    }

    write_c_str::write_c_str(const char *s)
    {
        std::strncpy(_s, s, 100);
        _s[100] = '\0';
    }

    std::ostream &operator<<(std::ostream &os, const write_c_str &manip)
    {
        os.write(manip._s, std::strlen(manip._s) + 1); 
        return os;
    }

    read_c_str::read_c_str(char *s, size_t size) : _s(s), _size(size) {}

    std::istream &operator>>(std::istream &is, const read_c_str &manip)
    {
        char ch;
        size_t i = 0;
        while (i < manip._size - 1 && is.get(ch))
        {
            manip._s[i++] = ch;
            if (ch == '\0') return is;
        }
        manip._s[i] = '\0'; 
        if (ch != '\0') is.setstate(std::ios::failbit); 
        return is;
    }
}
