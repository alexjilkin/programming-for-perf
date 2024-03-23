#include <vector>
#include <algorithm>

#pragma once

namespace pfp {

template <class dtype>
class vs {
  std::vector<dtype> v;
  bool isSorted = false;

  public:
    vs() {}

    void insert(dtype val) {
        v.push_back(val);
    }

    int count(dtype val) {
      if (!isSorted) {
        std::sort(v.begin(), v.end());
        isSorted = true;
      }

      return std::binary_search(v.begin(), v.end(), val);
    }
};

}  // namespace pfp
