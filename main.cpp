#include <iostream>

#include "perlin.hpp"

using namespace perlin;

float generate(float i, float j) {
    return perlin_2d(i, j) + 0.5 * perlin_2d(2 * i, 2 * j) + 0.25 * perlin_2d(4 * i, 4 * j);
}

void save_ppm(const std::vector<std::vector<float>>& values, float maxv, float minv) {
    if (values.size() == 0 || values[0].size() == 0) {
        std::cerr << "One or more dimensions are zero.\n";
        exit(1);
    }
    std::cout << "P3\n" << values.size() << " " << values[0].size() << "\n255\n";

    for (const auto& row : values) {
        for (const auto& value : row) {
            int pvalue = static_cast<int>((value - minv) / (maxv - minv) * 255);
            if (pvalue > 255 || pvalue < 0) {
                std::cerr << "Pixel value out of range: " << pvalue << "\n";
                exit(1);
            }
            std::cout << pvalue << " " << pvalue << " " << pvalue << "\n";
        }

        std::cout << "\n";
    }
}

int main() {
    std::vector<std::vector<float>> values;

    float maxv = -1e6;
    float minv = 1e6;
    for (int i = 0; i < 100; ++i) {
        std::vector<float> row;

        for (int j = 0; j < 100; ++j) {
            float v = generate(i / 10.0, j / 10.0);
            row.push_back(v);
            if (v > maxv) maxv = v;
            if (v < minv) minv = v;
        }

        values.push_back(row);
    }

    save_ppm(values, maxv, minv);

    return 0;
}
