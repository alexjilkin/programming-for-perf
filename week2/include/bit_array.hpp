#include <vector>
#pragma once

namespace weekTwo {

template <size_t n>
class BitArray {
public:
    std::vector<uint64_t> bits;

    BitArray() {
      bits.resize((n + 63) / 64);
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

    size_t sum(size_t pos) const {
        size_t count = 0;

        for (size_t i = 0; i <= pos / 64; i++) {
            if (i < pos / 64) {
                count += __builtin_popcountll(bits[i]);
            } else {
                uint64_t mask = (1ULL << (pos % 64 + 1)) - 1; // Create a mask for the relevant bits
                count += __builtin_popcountll(bits[i] & mask);
            }
        }

        return count;
    }

    size_t location(size_t l) const {
        size_t count = 0;

        for (size_t i = 0; i <= bits.end() / 64; i++) {
            if (bits[i] ) {
                count += __builtin_popcountll(bits[i]);
            } else {
                uint64_t mask = (1ULL << (bits.end() % 64 + 1)) - 1; // Create a mask for the relevant bits
                count += __builtin_popcountll(bits[i] & mask);
            }

            if (count == l) {
                return i;
            }
        }

        return count;
    }
};
} 