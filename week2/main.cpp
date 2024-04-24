#include "include/bit_array.hpp"
#include "include/packed_array.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>

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

  uint64_t n, m, val;
  auto start = std::chrono::high_resolution_clock::now();

  in->read(reinterpret_cast<char *>(&n), sizeof(n));
  in->read(reinterpret_cast<char *>(&m), sizeof(m));
  
  weekTwo::BitArray ba(m);

  std::vector<uint64_t> values(n);
  in->read(reinterpret_cast<char *>(values.data()),
                    n * sizeof(uint64_t));

  for (uint32_t i = 0; i < n; ++i) {
    ba.set(values[i], true);
  }

  if (is_output_time == true) {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cerr << (elapsed).count() << "\n";
  }

  start = std::chrono::high_resolution_clock::now();
  std::vector<uint64_t> queries(n);
  in->read(reinterpret_cast<char *>(queries.data()),
                    n * sizeof(uint64_t));

  for (uint32_t i = 0; i < n; ++i) {
    std::cout << ba.location(queries[i]) << '\n';
  }

  if (is_output_time == true) {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cerr << (elapsed).count() << "\n";
  }

  return 0;
}
