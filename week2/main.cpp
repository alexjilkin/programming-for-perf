#include <vector>
#include <stdexcept>
#include <iostream>
#include "include/bit_array.hpp"

int main() {
    weekTwo::BitArray<100> ba;
    ba.set(3, true);
    ba.set(95, true);

    std::cout << ba.get(3);
    return 0;
}
