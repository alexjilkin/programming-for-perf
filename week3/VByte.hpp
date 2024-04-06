#include <bitset>
#include <iostream>
#include <vector>

namespace weekThree {
class VByte {
  std::vector<uint8_t> blocks;

public:
  VByte() {}

  int encode(u_int64_t i) {
    while (true) {
      u_int8_t b = i % 128;
      if (i < 128) {
        blocks.push_back(b+128);

        return blocks.size();
      }
      blocks.push_back(b);
      i = i / 128;
    }

    return blocks.size();
  }

  uint64_t decode() const {
    uint64_t result = 0;
    for (int i = blocks.size() - 1; i >= 0; i--) {
      result =
          result * 128 +
          (blocks[i] & 0x7F); // Mask off the continuation bit before adding.
    }

    return result;
  }

  uint64_t size() const { return blocks.size(); }
};
} // namespace weekThree