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
    141, 128, 195, 78,  66,  215, 61,  156, 180};

namespace detail {

// in one dimension, the gradient is either 1 or -1
inline float grad_1d(const int x) {
    size_t idx = x % p_size;
    if (idx < 0) {
        idx += p_size;
    }

    if (permutation[idx] & 1) {
        return -1.0;
    } else {
        return 1.0;
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

    return 0.0;
}

template <typename T>
inline T perlin_1d(const T x, const T t = 0) {
    if (t != 0) {
        return perlin_2d(x, t);
    }

    int x0 = std::floor(x);
    int x1 = x0 + 1;

    T dx = x - x0;
    T fade_x = detail::fade(dx);

    T g0 = detail::grad_1d(x0);
    T g1 = detail::grad_1d(x1);

    return (1.0 - fade_x) * g0 * dx + fade_x * g1 * (dx - 1);
}

}  // namespace perlin

#endif
