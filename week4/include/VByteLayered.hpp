#include "bit_array.hpp"
#include <cstdint>
#include <vector>

namespace weekFour {

class VByteLayered {
private:
  std::vector<BitArray> B;             
  std::vector<std::vector<uint8_t>> A; 
  size_t k;                            
  size_t n;                            
  size_t j;

public:
  VByteLayered(size_t k_, size_t n_) : k(k_), n(n_), j(0) {
    B.emplace_back(BitArray(n));
  }

  void add(uint64_t value) {
    auto blocks = encode(value);

    while (B.size() < blocks.size()) {
      B.emplace_back(BitArray(n)); 
      A.emplace_back();
    }

    for (size_t i = 0; i < blocks.size(); ++i) {
      B[i].set(j, blocks[i][0]); 

      uint64_t data_block = 0;
      for (size_t bit = 1; bit < 8; ++bit) {
        if (blocks[i][bit]) {
          data_block |= (1ULL << bit);
        }
      }

      A[i].push_back(data_block);
    }

    ++j;
  }

  uint64_t get(size_t index) {
    uint64_t result = 0;
    size_t layer = 0;

    while (true) {
        bool stopBit = B[layer].get(index); 

        if (stopBit) {
            break; 
        }
        size_t y = index - B[layer].sum(index);
        result = (result << 1) | A[layer][y]; 

        ++layer; 
    }

    return result;
}

  std::vector<std::vector<bool>> encode(uint64_t i) {
    uint64_t base = 1ULL << (k - 1);
    std::vector<std::vector<bool>> blocks;
    while (true) {
      uint64_t b = i % base;
      std::vector<bool> currentBlock(k, false);

      for (size_t bit = 0; bit < k - 1; ++bit) {
        currentBlock[bit] = (b >> bit) & 1;
      }
      if (i < base) {
        currentBlock[k - 1] = true;
        blocks.push_back(currentBlock);
        break;
      } else {
        blocks.push_back(currentBlock);
      }

      i /= base;
    }

    return blocks;
  }
};

} // namespace weekFour
