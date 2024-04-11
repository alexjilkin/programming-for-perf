#pragma once

#include <vector>
#include <algorithm>
#include "bit_array.hpp"
#include <cmath>
namespace pfp {
template <class dtype>
class fast {
  pfp::BitArray ba;

private:
  uint64_t max = pow(2, 19) - 1;
public:
  fast() : ba(pow(2, 19) - 1) {}

  void insert(dtype pos) {
    ba.set(pos & max, true);
  }

  int count(dtype pos) {
    return ba.get(pos & max); 
  }
};

} // namespace pfp
