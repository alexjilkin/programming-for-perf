#include "include/bit_array.hpp"
#include "include/packed_array.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]) {
  bool is_output_time = false;
  bool is_sum = false;
  bool is_location = false;
  bool is_packed_integers = false;

  std::ifstream file_stream; // File stream for reading from a file, if provided
  std::istream *in = nullptr; // Pointer to abstract input stream

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-t") {
      is_output_time = true;
    } else if (arg == "-s") {
      is_sum = true;
    } else if (arg == "-l") {
      is_location = true;
    } else if (arg == "-i") {
      is_packed_integers = true;
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

  if (is_packed_integers) {
    std::uint64_t n, k, val;

    in->read(reinterpret_cast<char *>(&n), sizeof(n));
    in->read(reinterpret_cast<char *>(&k), sizeof(k));

    weekTwo::PackedIntegerArray pi(n, k);

    auto start = std::chrono::high_resolution_clock::now();
    for (std::uint64_t j = 0; j < n; ++j) {
      if (!in->read(reinterpret_cast<char *>(&val), sizeof(val))) {
        std::cerr << "Error reading value from the input." << std::endl;
        break;
      }
      pi.append(val);
    }
    if (is_output_time == true) {
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end - start;
      std::cerr << (elapsed).count() << "\n";
    }

    start = std::chrono::high_resolution_clock::now();
    for (std::uint64_t j = 0; j < n; ++j) {
      if (!in->read(reinterpret_cast<char *>(&val), sizeof(val))) {
        std::cerr << "Error reading value from the input." << std::endl;
        break;
      }
      std::cout << pi.get(val) << "\n";
    }

    if (is_output_time == true) {
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = end - start;
      std::cerr << (elapsed).count() << "\n";
    }

    return 0;
  }

  std::uint64_t n, m, val;

  if (!in->read(reinterpret_cast<char *>(&n), sizeof(n)) ||
      !in->read(reinterpret_cast<char *>(&m), sizeof(m))) {
    std::cerr << "Error reading n or m from the input." << std::endl;
    return 1;
  }

  weekTwo::BitArray ba(m);

  auto start = std::chrono::high_resolution_clock::now();

  for (std::uint64_t j = 0; j < n; ++j) {
    if (!in->read(reinterpret_cast<char *>(&val), sizeof(val))) {
      std::cerr << "Error reading value from the input." << std::endl;
      break;
    }
    ba.set(val, true);
  }
  if (is_output_time == true) {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cerr << (elapsed).count() << "\n";
  }

  start = std::chrono::high_resolution_clock::now();
  for (std::uint64_t k = 0; k < n; ++k) {
    if (!in->read(reinterpret_cast<char *>(&val), sizeof(val))) {
      std::cerr << "Error reading value from the input." << std::endl;
      break;
    }

    std::cout << (is_location ? ba.location(val)
                  : is_sum    ? ba.sum(val)
                              : ba.get(val))
              << "\n";
  }
  if (is_output_time == true) {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cerr << (elapsed).count() << "\n";
  }

  return 0;
}
