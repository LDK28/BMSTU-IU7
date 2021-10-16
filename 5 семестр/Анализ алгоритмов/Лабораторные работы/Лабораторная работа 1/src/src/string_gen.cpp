#include "string_gen.hpp"

string string_gen(size_t len) {
    string new_str;
    for (size_t i = 0; i < len; i++)
        new_str.push_back(rand() % 170 - 48);
    return new_str;
}
