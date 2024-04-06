#include "./VByte.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]) {
  bool is_output_time = false;

  std::ifstream file_stream; // File stream for reading from a file, if provided
  std::istream *in = nullptr; // Pointer to abstract input stream

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-t") {
      is_output_time = true;
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

  std::uint64_t n, val;
  std::vector<weekThree::VByte> vbs;

  in->read(reinterpret_cast<char *>(&n), sizeof(n));
  int blocksCount = 0;

  for (std::uint64_t j = 0; j < n; ++j) {
    in->read(reinterpret_cast<char *>(&val), sizeof(val));
    auto vb = weekThree::VByte();
    blocksCount += vb.encode(val);
    vbs.push_back(vb);
  }

  std::cerr << blocksCount << std::endl;

  for (const weekThree::VByte &a : vbs) {
    std::cerr << a.decode() << std::endl;
  }

  return 0;
}
