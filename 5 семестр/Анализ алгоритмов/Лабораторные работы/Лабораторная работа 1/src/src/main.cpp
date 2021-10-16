#include <iostream>
#include <string>
#include "time_compare.hpp"
#include "manual_input.hpp"

using namespace std;

int main() {
    size_t rc;
    cout << "1: manually enter\n"
            "2: compare time\n\n"
            "0: exit\n";
    cin >> rc;
    while (rc == 1 || rc == 2)
    {
        if (rc == 1)
            manual_input();
        else
            time_compare();
        cout << "1: manually enter\n"
                "2: compare time\n\n"
                "0: exit\n";
        cin >> rc;
    }
    return 0;
}
