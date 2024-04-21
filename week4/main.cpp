#include "include/VByteLayered.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]) {
  auto startWallClock = std::chrono::high_resolution_clock::now();
  bool outputTime = false;

  std::ifstream file_stream;
  std::istream *inputStream = nullptr;

  // Parsing command line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-t") {
      outputTime = true;
    } else if (arg[0] != '-') {
      file_stream.open(arg, std::ios::binary);
      if (!file_stream.is_open()) {
        std::cerr << "Error opening file: " << arg << std::endl;
        return 1;
      }
      inputStream = &file_stream;
    }
  }

  if (!inputStream) {
    inputStream = &std::cin;
  }

  uint64_t n, val;

  inputStream->read(reinterpret_cast<char *>(&n), sizeof(n));
  weekFour::VByteLayered vbytes(n);

  for (uint64_t i = 0; i < n; ++i) {
    inputStream->read(reinterpret_cast<char *>(&val), sizeof(val));
    // std::cout << val << std::endl;

    vbytes.add(val);
  }

  uint64_t q, val_q;
  inputStream->read(reinterpret_cast<char *>(&q), sizeof(q));
  for (uint64_t i = 0; i < q; ++i) {
    inputStream->read(reinterpret_cast<char *>(&val_q), sizeof(val_q));


    std::cout << vbytes.get(val_q) << std::endl;
   
  }

  if (outputTime) {
    auto endWallClock = std::chrono::high_resolution_clock::now();
    auto elapsedWallClock = std::chrono::duration<double, std::milli>(
        endWallClock - startWallClock);
    std::cerr << "Elapsed wall-clock time: " << elapsedWallClock.count()
              << " ms\n";
  }

  return 0;
}
