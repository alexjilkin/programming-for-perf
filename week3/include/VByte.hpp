#include <iostream>
#include <vector>

namespace weekThree {

class VByte {
private:
  std::vector<std::vector<bool>> blocks;
  size_t k; 
  u_int64_t base;

public:
  VByte(size_t size) : k(size), base(1ULL << (k - 1)) {}

  int encode(uint64_t i) {
    while (true) {
      uint64_t b = i % base;
      std::vector<bool> currentBlock(
          k, false); // Initialize a block of size 'k' with false

      for (size_t bit = 0; bit < k - 1; ++bit) {
        currentBlock[bit] = (b >> bit) & 1;
      }
      if (i < base) {
        currentBlock[k - 1] =
            true; 
        blocks.push_back(currentBlock);
        break;
      } else {
        blocks.push_back(currentBlock);
      }

      i /= base;
    }

    return blocks.size();
  }

  uint64_t decode() const {

    uint64_t result = 0;
    uint64_t multiplier = 1;
    for (const auto &block : blocks) {
      uint64_t blockValue = 0;
      for (size_t bit = 0; bit < k - 1; ++bit) {
        if (block[bit]) {
          blockValue |= (1ULL << bit);
        }
      }
      result += blockValue * multiplier;
      multiplier *= base;
    }

    return result;
  }

  uint64_t size() const { return blocks.size(); }
};

}
