#ifndef INC_01_LEVENSTEIN_HPP
#define INC_01_LEVENSTEIN_HPP

#include <string>
using namespace std;

size_t matr_method(const string &str1, const string &str2);

size_t recur_method(const string &str1, const string &str2);

size_t rec_cache_method(const string &str1, const string &str2);

size_t Domerau_method(const string &str1, const string &str2);

#endif
