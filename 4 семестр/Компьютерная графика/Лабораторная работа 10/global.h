#ifndef GLOBAL_H
#define GLOBAL_H

template <typename T>
constexpr T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
constexpr T max(T a, T b, T c, T d) {
    return max(max(a, b), max(c, d));
}

#endif // GLOBAL_H
