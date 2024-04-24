#include <chrono>
#include <stdexcept>
#include <vector>
#pragma once

namespace weekTwo {

class BitArray {
public:
  std::vector<uint64_t> bits;
  std::vector<uint32_t> bitCounts;
  std::vector<uint32_t> comCounts;
  bool isCom = false;

  explicit BitArray(size_t n)
      : bits((n + 63) / 64), bitCounts((n + 63) / 64, 0),
        comCounts((n + 63) / 64, 0) {}

  bool get(size_t pos) const { return (bits[pos >> 6] >> (pos & 63)) & 1; }

  void set(size_t pos, bool value) {

    size_t index = pos >> 6;
    size_t bit = pos & 63;
    uint64_t mask = 1ULL << bit;
    bool currentBit = (bits[index] & mask) != 0;

    if (value && !currentBit) {
      bits[index] |= mask;
      ++bitCounts[index];
    } else if (!value && currentBit) {
      bits[index] &= ~mask;
      --bitCounts[index];
    }
  }

  void calcComCounts() {
    if (isCom == false) {
      comCounts[0] = bitCounts[0];

      for (int32_t i = 1; i < bitCounts.size(); i++) {
        comCounts[i] = comCounts[i - 1] + bitCounts[i];
      }

      isCom = true;
    }
  }
  size_t sum(size_t pos) {
    size_t maxIndex = pos >> 6;
    uint64_t mask = (1ULL << (pos & 63)) - 1;
    uint32_t sum = 0;

    for (size_t i = 0; i < maxIndex; ++i) {
      sum += bitCounts[i];
    }

    sum += __builtin_popcountll(bits[maxIndex] & mask);

    return sum;
  }

  size_t location(u_int32_t i) {
    u_int32_t left = 0;
    u_int32_t right = (bits.size() << 6) - 1;

    while (left < right) {
      u_int32_t mid = left + ((right - left) >> 1);

      if (sum(mid) < i) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return left;
  }
};
} // namespace weekTwo
