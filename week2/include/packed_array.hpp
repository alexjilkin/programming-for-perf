#include <stdexcept>
#include <vector>
#include <stdexcept>

namespace weekTwo {
class PackedIntegerArray {
public:

  std::vector<uint64_t> data;
  size_t k;
  size_t count;
  size_t capacity;

  PackedIntegerArray(size_t n, size_t k) : k(k), count(0), capacity(n) {
    if (k > 64 || k == 0)
      throw std::invalid_argument("k must be between 1 and 64.");
    // Calculate the total number of 64-bit blocks needed
    size_t totalBits = n * k;
    data.resize((totalBits + 63) / 64, 0);
  }

  void append(uint64_t value) {
    if (count >= capacity)
      throw std::out_of_range("Array is full.");
    // Ensure value fits within k bits
    value &= (1ULL << k) - 1;

    size_t bitPos = count * k;
    size_t index = bitPos / 64;
    size_t offset = bitPos % 64;

    data[index] |= value << offset;

    if (offset + k > 64) {
      data[index + 1] = value >> (64 - offset);
    }

    ++count;
  }

  uint64_t get(size_t index) const {
    if (index >= count)
      throw std::out_of_range("Index out of bounds.");

    size_t bitPos = index * k;
    size_t arrayIndex = bitPos / 64;
    size_t offset = bitPos % 64;

    uint64_t value = data[arrayIndex] >> offset;

    if (offset + k > 64) {
      value |= data[arrayIndex + 1] << (64 - offset);
    }
    value &= (1ULL << k) - 1;

    return value;
  }
};
}
