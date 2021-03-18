#include <iostream>
#include <string>

// Code by https://github.com/ReneNyffenegger

struct BASE64_DEC_TABLE {
    signed char n[256];

    BASE64_DEC_TABLE() {
        for (int i = 0; i < 256; ++i)    n[i] = -1;
        for (unsigned char i = '0'; i <= '9'; ++i) n[i] = 52 + i - '0';
        for (unsigned char i = 'A'; i <= 'Z'; ++i) n[i] = i - 'A';
        for (unsigned char i = 'a'; i <= 'z'; ++i) n[i] = 26 + i - 'a';
        n['+'] = 62;
        n['/'] = 63;
    }
    int operator [] (unsigned char i) const { return n[i]; }
};

size_t Base64Decode(const std::string& source, void* pdest, size_t dest_size) {
    static const BASE64_DEC_TABLE b64table;
    if (!dest_size) return 0;
    const size_t len = source.length();
    int bc = 0, a = 0;
    char* const pstart = static_cast<char*>(pdest);
    char* pd = pstart;
    char* const pend = pd + dest_size;
    for (size_t i = 0; i < len; ++i) {
        const int n = b64table[source[i]];
        if (n == -1) continue;
        a |= (n & 63) << (18 - bc);
        if ((bc += 6) > 18) {
            *pd = a >> 16; if (++pd >= pend) return pd - pstart;
            *pd = a >> 8;  if (++pd >= pend) return pd - pstart;
            *pd = a;       if (++pd >= pend) return pd - pstart;
            bc = a = 0;
        }
    }
    if (bc >= 8) {
        *pd = a >> 16; if (++pd >= pend) return pd - pstart;
        if (bc >= 16) *(pd++) = a >> 8;
    }
    return pd - pstart;
}