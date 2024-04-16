#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include "include/VByteLayered.hpp" 

int main(int argc, char *argv[]) {
    auto startWallClock = std::chrono::high_resolution_clock::now();
    bool outputTime = false;
    size_t k = 7; 

    std::ifstream file_stream; 
    std::istream* inputStream = nullptr;

    // Parsing command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-t") {
            outputTime = true;
        } else if (arg == "-k") {
            k = std::stoi(argv[++i]);  // Increment i to skip next argument
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
    weekFour::VByteLayered vbytes(k, n);

    for (uint64_t i = 0; i < n; ++i) {
        inputStream->read(reinterpret_cast<char *>(&val), sizeof(val));
        vbytes.add(val);
    }

    uint64_t q;
    inputStream->read(reinterpret_cast<char *>(&q), sizeof(q));
    for (uint64_t i = 0; i < q; ++i) {
        inputStream->read(reinterpret_cast<char *>(&val), sizeof(val));
        try {
            std::cout << vbytes.get(val) << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Output elapsed time if requested
    if (outputTime) {
        auto endWallClock = std::chrono::high_resolution_clock::now();
        auto elapsedWallClock = std::chrono::duration<double, std::milli>(endWallClock - startWallClock);
        std::cout << "Elapsed wall-clock time: " << elapsedWallClock.count() << " ms\n";
    }

    return 0;
}
