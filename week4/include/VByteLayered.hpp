#include "bit_array.hpp"
#include <bitset>
#include <cstdint>
#include <vector>

namespace weekFour {

class VByteLayered {
private:
  std::vector<BitArray> B;
  std::vector<std::vector<uint8_t>> A;
  size_t n;
  size_t j;

public:
  VByteLayered(size_t n_) : n(n_), j(0) {}

  void add(uint64_t value) {
    std::vector<uint8_t> encoded_blocks = encode(value);

    while (B.size() < encoded_blocks.size()) {
      B.emplace_back(BitArray(n));
      A.emplace_back();
    }

    for (size_t i = 0; i < encoded_blocks.size(); ++i) {
      // std::cout << std::bitset<8>(encoded_blocks[i]) << std::endl;

      bool stopBit =
          encoded_blocks[i] & (1 << 7); // Check the MSB for the stop bit

      B[i].set(j, stopBit);
    //   std::cout << B[i].get(j) << std::endl;

      uint8_t data_block = encoded_blocks[i];
      A[i].push_back(data_block);
    }

    ++j;
  }

  uint64_t get(size_t index) const {
    size_t layer = 0;
    std::vector<uint8_t> blocks;

    bool stopBit = B[layer].get(index);

    size_t y = index - B[layer].sum(index);

    blocks.push_back(A[0][index]);
    if (stopBit) {
      return decode(blocks);
    }

    layer++;

    while (true) {
      blocks.push_back(A[layer][y]);
    //   std::cout << std::bitset<8>(A[layer][y]) << std::endl;

      stopBit = B[layer].get(index);
      if (stopBit) {
        return decode(blocks);
      }

      y = y - B[layer].sum(y);
      layer++;
    }
  }

  std::vector<uint8_t> encode(u_int64_t i) {
    std::vector<uint8_t> blocks;

    while (true) {
      u_int8_t b = i % 128;
      if (i < 128) {
        blocks.push_back(b + 128);

        return blocks;
      }
      blocks.push_back(b);
      i = i / 128;
    }

    return blocks;
  }

  uint64_t decode(std::vector<uint8_t> blocks) const {
    uint64_t result = 0;
    for (int i = blocks.size() - 1; i >= 0; i--) {
      result = result * 128 + (blocks[i] & 0x7F);
    }

    return result;
  }
};

} // namespace weekFour
