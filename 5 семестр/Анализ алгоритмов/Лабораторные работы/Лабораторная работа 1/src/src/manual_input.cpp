#include "manual_input.hpp"
#include "levenstein.hpp"
#include <iostream>

void manual_input() {
    string str1, str2;
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;
    cout << "Result by matrix method: " << matr_method(str1, str2) << endl;
    cout << "Result by recursive method: " << recur_method(str1, str2) << endl;
    cout << "Result by recursive method with cache: " << rec_cache_method(str1, str2) << endl;
    cout << "Result by recursive method with cache for Domerau-Levenstein: " << Domerau_method(str1, str2) << endl;
}
