#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <random>

// TODO: octaves, shuffling/permutation, think about perm vs actual random?, 4d

namespace perlin {

// Taken from Ken Perlin's reference implementation
size_t p_size = 256;
int permutation[] = {
    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103,
    30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190, 6,   148, 247, 120, 234, 75,  0,   26,
    197, 62,  94,  252, 219, 203, 117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174,
    20,  125, 136, 171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158, 231,
    83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,  245, 40,  244, 102, 143,
    54,  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,  18,  169, 200, 196,
    135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124,
    123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,
    182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101,
    155, 167, 43,  172, 9,   129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185,
    112, 104, 218, 246, 97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,
    51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184, 84,  204, 176,
    115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,  222, 114, 67,  29,  24,  72,  243,
    141, 128, 195, 78,  66,  215, 61,  156, 180, 151, 160, 137, 91,  90,  15,  131, 13,  201, 95,
    96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,
    190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117, 35,  11,  32,
    57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175, 74,  165, 71,
    134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105,
    92,  41,  55,  46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
    76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198,
    173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,
    212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248,
    152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253, 19,
    98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228, 251, 34,  242, 193,
    238, 210, 144, 12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214,
    31,  181, 199, 106, 157, 184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236,
    205, 93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180};

namespace detail {

inline int hash(const int x, const int y, const int z) {
    return permutation[permutation[permutation[x] + y] + z];
}

// in one dimension, the gradient is either 1 or -1
template <typename T>
inline T grad(const int h, const T x, const T y, const T z) {
    switch (h & 0xF) {
        case 0x0:
            return x + y;
        case 0x1:
            return -x + y;
        case 0x2:
            return x - y;
        case 0x3:
            return -x - y;
        case 0x4:
            return x + z;
        case 0x5:
            return -x + z;
        case 0x6:
            return x - z;
        case 0x7:
            return -x - z;
        case 0x8:
            return y + z;
        case 0x9:
            return -y + z;
        case 0xA:
            return y - z;
        case 0xB:
            return -y - z;
        case 0xC:
            return y + x;
        case 0xD:
            return -y + z;
        case 0xE:
            return y - x;
        case 0xF:
            return -y - z;
        default:
            return 0;
    }
}

// easing function
template <typename T>
inline T fade(const T value) {
    return value * value * value * (value * (value * 6 - 15) + 10);
}

// linear interpolation between a and b at value v in [0, 1]
template <typename T>
inline T lerp(const T v, const T a, const T b) {
    return a + v * (b - a);
}

}  // namespace detail

template <typename T>
inline T perlin_3d(T x, T y, T z, T t = 0) {
    if (t == 0) {
        return 0.0;
    } else {
        return 0.0;
    }
}

template <typename T>
inline T perlin_2d(T x, T y, T t = 0) {
    if (t != 0) {
        return perlin_3d(x, y, t);
    }

    // the grid cell (square) that (x, y) is in
    int xi = std::floor(x);
    int yi = std::floor(y);

    T dx = x - xi;
    T dy = y - yi;

    T u = detail::fade(dx);
    T v = detail::fade(dy);

    T g00 = detail::grad(detail::hash(xi, yi, 0), dx, dy, T(0));
    T g01 = detail::grad(detail::hash(xi, yi + 1, 0), dx, dy - 1, T(0));
    T g10 = detail::grad(detail::hash(xi + 1, yi, 0), dx - 1, dy, T(0));
    T g11 = detail::grad(detail::hash(xi + 1, yi + 1, 0), dx - 1, dy - 1, T(0));

    T x0 = detail::lerp(u, g00, g10);
    T x1 = detail::lerp(u, g01, g11);

    return detail::lerp(v, x0, x1);
}

template <typename T>
inline T perlin_1d(const T x, const T t = 0) {
    if (t != 0) {
        return perlin_2d(x, t);
    }

    // the grid cell (just an interval) that x is in
    int xi = std::floor(x);

    T dx = x - xi;

    T u = detail::fade(dx);

    T g0 = detail::grad(detail::hash(xi, 0, 0), dx, T(0), T(0));
    T g1 = detail::grad(detail::hash(xi + 1, 0, 0), dx - 1, T(0), T(0));

    return detail::lerp(u, g0, g1);
}

}  // namespace perlin

#endif
