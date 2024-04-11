#pragma once

#include "bit_array.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
namespace pfp {
template <class dtype> class fast {

public:
  static constexpr uint32_t max = (1 << 19) - 1;

  std::vector<uint64_t> bits;

  fast() : bits((max + 63) / 64) {}

  bool count(dtype pos) const {
    dtype npos = pos & max;
    return (bits[npos >> 6] >> (npos & 63)) & 1;
  }

  void insert(dtype pos) {
    dtype npos = pos & max;

    bits[npos >> 6] |= 1ULL << (npos & 63);
  }
};

} // namespace pfp
