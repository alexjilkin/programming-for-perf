#include "./VByte.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <functional>

int main(int argc, char *argv[]) {
  bool is_output_time = false;
  bool is_sorted = false;

  std::ifstream file_stream; 
  std::istream *in = nullptr;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-t") {
      is_output_time = true;
    } else if (arg == "-s") {
      is_sorted = true;
    } else if (arg[0] != '-') {
      file_stream.open(arg, std::ios::binary);
      if (!file_stream.is_open()) {
        std::cerr << "Error opening file: " << arg << std::endl;
        return 1;
      }
      in = &file_stream;
    }
  }

  if (!in) {
    in = &std::cin;
  }

  std::vector<weekThree::VByte> vbs;
  std::uint64_t val, n, current = 0, blocksCount = 0;

  std::function<std::uint64_t(std::uint64_t)> getValue =
      [&](std::uint64_t newValue) -> std::uint64_t {
    if (is_sorted) {
      std::uint64_t diff = newValue - current;
      current = newValue; 
      return diff;
    } else {
      return newValue;
    }
  };

  in->read(reinterpret_cast<char *>(&n), sizeof(n));

  for (std::uint64_t j = 0; j < n; ++j) {
    in->read(reinterpret_cast<char *>(&val), sizeof(val));
    auto vb = weekThree::VByte();
    blocksCount += vb.encode(getValue(val));
    vbs.push_back(vb);
  }

  std::cerr << blocksCount << std::endl;

  current = 0;

  for (const weekThree::VByte &a : vbs) {
    if (is_sorted) {
      current += a.decode();
      std::cerr << current << std::endl;
    } else {
      std::cerr << a.decode() << std::endl;
    }
  }
}
