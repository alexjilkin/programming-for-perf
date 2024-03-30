#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "include/bit_array.hpp"

int main(int argc, char const* argv[]) {
    bool strerr_output = false;
    int input_file = 0;

    for (int i = 1; i < argc; ++i) {
        std::string s(argv[i++]);
        if (s.compare("-t") == 0) {
        } else if (s.compare("-b") == 0) {

        } else {
          input_file = i - 1;
        }
      
    }
    // if (input_file > 0) {
      
    // }

    weekTwo::BitArray<200> ba;
    std::ifstream in(argv[input_file], std::ios::binary);
    std::uint64_t n, m, val;

    // Read the first two 64-bit integers
    if (!in.read(reinterpret_cast<char*>(&n), sizeof(n)) ||
        !in.read(reinterpret_cast<char*>(&m), sizeof(m))) {
        std::cerr << "Error reading n or m from the file." << std::endl;
        return 1;
    }

    // std::cout << n << std::endl;
    // std::cout << m << std::endl;

    for (uint64_t i = 1; i < n; ++i) {
      if (!in.read(reinterpret_cast<char*>(&val), sizeof(val))) {
          std::cerr << "Error reading value from the file." << std::endl;
          break; // Exit the loop if we cannot read more (e.g., end of file)
      }
      ba.set(val, true);
    }


    std::cout << ba.get(3) << "\n";
    std::cout << ba.get(4) << "\n";
    std::cout << ba.sum(n) << "\n";
    return 0;
}
