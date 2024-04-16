#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace weekFour {

class BitArray {
public:
  std::vector<uint_fast64_t> bits;

  explicit BitArray(size_t n) : bits((n + 63) / 64) {}

  bool get(size_t pos) const { return (bits[pos >> 6] >> (pos & 63)) & 1; }

  void set(size_t pos, bool value) {
    size_t index = pos >> 6;
    size_t bit = pos & 63;

    if (value) {
      bits[index] |= 1ULL << bit;
    } else {
      bits[index] &= ~(1ULL << bit);
    }
  }

  size_t sum(size_t pos) const {
    size_t count = 0;

    for (size_t i = 0; i <= pos / 64; i++) {
      if (i < pos / 64) {
        count += __builtin_popcountll(bits[i]);
      } else {
        uint64_t mask = (1ULL << (pos % 64)) - 1;
        count += __builtin_popcountll(bits[i] & mask);
      }
    }

    return count;
  }

  size_t location(size_t i) const {
    size_t left = 0;
    size_t right = bits.size() * 64 - 1;

    while (left < right) {
      size_t mid = left + (right - left) / 2;

      if (sum(mid) < i) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return left;
  }
};

} // namespace weekFour
