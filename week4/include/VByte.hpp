#include <cmath> 
#include <vector>

namespace weekFour {

class VByte {
private:

public:
  std::vector<std::vector<bool>> blocks;
  size_t k;
  uint64_t base;
  VByte(size_t size) : k(size), base(std::pow(2, k - 1)) {}

  void encode(uint64_t i) {
    while (true) {
      uint64_t b = i % base;
      std::vector<bool> currentBlock(k, false);
      for (size_t bit = 0; bit < k - 1; ++bit) {
        currentBlock[bit] = (b >> bit) & 1;
      }
      currentBlock[k - 1] = (i < base); 
      blocks.push_back(currentBlock);
      if (i < base)
        break;
      i /= base;
    }
  }

  uint64_t decode() const {
    uint64_t result = 0;
    uint64_t multiplier = 1;
    for (const auto &block : blocks) {
      uint64_t blockValue = 0;
      for (size_t bit = 0; bit < k - 1; ++bit) {
        if (block[bit])
          blockValue |= (1ULL << bit);
      }
      result += blockValue * multiplier;
      if (block[k - 1])
        break; // Last block marked by the most significant bit
      multiplier *= base;
    }
    return result;
  }

  size_t blockCount() const { return blocks.size(); }
};

class VBytes {
private:
  std::vector<VByte> bytes;

public:
  void addVByte(const VByte &vbyte) { bytes.push_back(vbyte); }

  uint64_t scan(size_t target) {
    for (size_t i = 0; i < bytes.size(); ++i) {
      if (i == target) {
        return bytes[i].decode(); 
      }
    }
    throw std::runtime_error("Target not found");
  }

  size_t size() const { return bytes.size(); }
};

} // namespace weekThree
