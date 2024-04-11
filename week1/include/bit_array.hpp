#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace pfp {

class BitArray {
public:
    std::vector<uint_fast64_t> bits;

    explicit BitArray(size_t n) : bits((n + 63) / 64) {}

    bool get(size_t pos) const {
        return (bits[pos >> 6] >> (pos & 63)) & 1;
    }

    void set(size_t pos, bool value) {
        size_t index = pos >> 6;
        size_t bit = pos & 63;

        if (value) {
            bits[index] |= 1ULL << bit;
        } else {
            bits[index] &= ~(1ULL << bit);
        }
    }
};

} // namespace pfp
