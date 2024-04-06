#include <vector>
#include <iostream>
#include <bitset>

namespace weekThree {
class VByte {
    std::vector<uint8_t> blocks;
public:
    VByte() {}

    void print() {
        std::cout << "crap" << "\n";
    }

    int encode(u_int64_t i) {        
        int count = 1;

        while (true) {
            u_int8_t b = i % 128;
            if (i < 128) {
                // std::cout << std::bitset<8>(b + 128) << std::endl;
                blocks.push_back(b);
                break;
            }
            
            // auto res = std::bitset<8>(b);
            blocks.push_back(b);
            // std::cout << res << std::endl;
            i = i / 128;
            count++;
        }

        return count;
    }

    uint64_t decode() const {
        uint64_t result = 0;
        for (int i = blocks.size() - 1; i >= 0; i--) {
            result = result * 128 + (blocks[i] & 0x7F); // Mask off the continuation bit before adding.
        }

        return result;
    }
};
}