#include <iostream>

#include "perlin.hpp"

using namespace perlin;

int main() {
    for (float i = 0; i < 1.0; i += 0.05) {
        std::cout << perlin_1d(i) << ",";
    }
    std::cout << '\n';

    return 0;
}
