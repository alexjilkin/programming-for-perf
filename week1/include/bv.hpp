/**
 * You can use this for programming task 2 of set 1 
*/

#pragma once

namespace pfp {

template <class dtype>
class bv {
  std::vector<bool> v;

  public:
    bv(dtype limit) {
      // std::cout << "5";
      v = std::vector<bool>(limit, false);
    }

    void insert(dtype value) { 
      v[value] = true;
    }

    int count(dtype value) const {
        return v[value];
    }
};

} // namespace pfp