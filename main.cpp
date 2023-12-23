#include <iostream>

#include "perlin.hpp"

using namespace perlin;

int main() {
    for (float i = 0; i < 8.0; i += 0.02) {
        // std::cout << perlin_1d(i) + perlin_1d(i * 2) / 2 + perlin_1d(i * 4) / 4 << "\n";
        std::cout << perlin_1d(i) << "\n";
    }

    return 0;
}
