#include <vector>
#include <algorithm>

#pragma once

namespace pfp {

template <class dtype>
class fast {
  std::vector<bool> values;
  dtype maxKey = 0;

public:
  fast() : values() {}

  void insert(dtype val) {
      values[val] = true;
  }

  int count(dtype val) {
      return values[val];
  }
};

}
