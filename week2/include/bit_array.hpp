#include <vector>
#pragma once

namespace weekTwo {

template <size_t n>
class BitArray {
public:
    std::vector<uint64_t> bits;

    BitArray() {
      bits.resize(n);
    }

    bool get(size_t pos) const {
        if (pos >= bits.size() * 64) {
            throw std::out_of_range("Bit position out of range.");
        }
        return (bits[pos / 64] >> (pos % 64)) & 1;
    }

    void set(size_t pos, bool value) {
        if (pos >= bits.size() * 64) {
            throw std::out_of_range("Bit position out of range.");
        }
        if (value) {
            bits[pos / 64] |= 1ULL << (pos % 64);
        } else {
            bits[pos / 64] &= ~(1ULL << (pos % 64));
        }
    }
};
} 