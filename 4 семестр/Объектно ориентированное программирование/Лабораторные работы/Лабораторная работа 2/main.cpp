#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <exception>

#include "myErrors.h"
#include "Vector.hpp"

using namespace std;

int main()
{
    try
    {
        cout << "Test constructors\n\n";

        Vector<double> v1;
        cout << "Default:\n";
        cout << v1 << "\n";

        cout << "With parameters: \n";
        Vector<double> v2(2, 3., 4.);
        Vector<double> v3(3, 3.0, 4.0, 0.0);
        cout << v2 << "\n" << v3 << "\n";
        
        cout << "From array: \n";
        double arr[5] = {5, 1, 7, 4, 0};
        Vector<double> v4(5, arr);
        cout << v4 << "\n";

        cout << "From existing vector:\n";
        Vector<double> v5(v3);
        cout << v5 << "\n";


        cout << "\nTest methods\n\n";

        cout << "Length of vector (3, 4, 0): " << v3.len() << endl;
        cout << "Size of vector (3, 4, 0): " << v3.size() << endl;
        cout << "Get second element {5, 1, 7, 4, 0}: "<< v4.get_elem_Vector(1) << endl;

        cout << "Multiply by 10: " << (v4 *= 10) << endl;
        cout << "Divide by 10: " << (v4 /= 10) << endl;
        cout << "Subtract two vectors {5, 1, 7, 4, 0} minus {3, 4, 0}: " << (v4 -= v3) << endl;
        cout << "Change to opposite direction (unary minus) {3, 4, 0}: " << (-v3) << endl << endl;

        Vector<double> v12{1., 2., 3., 4., 5.};
        cout << "Init vector {1., 2., 3., 4., 5.}: " << v12 << endl;
        v12[2] = 10.;
        cout << "Change third element using [2]: " << v12 << endl;
        v12.set_elem_Vector(3, 11.);
        cout << "Change fourth element using set_elem_Vector method: " << v12 << endl;
        v12 = v12.get_single_vector();
        cout << "Get vector with lenght of one: " << v12 << endl << endl;

        Vector<double> v6(3, 3.0, 4.0, 0.0);
        cout << "Vector multiplication {3,4,0} and {3,4,0}: " << (v3 &= v6) << endl;
        Vector<int> v7(2, 10, 0);
        Vector<int> v8(2, 0, 10);
        cout << "Find angle between {10, 0} and {0, 10}: " << v7.angle_between_vectors(v8) << endl;
        Vector<double> v9(2, 5., 5.);
        Vector<double> v10(2, 10., 0.0);
        cout << "Fing angle between {5, 5} and {10, 0}: " << v9.angle_between_vectors(v10) << endl;
        Vector<double> v20(2, 20., 20.0);
        cout << "Check collinearity of {5, 5} and {20, 20}: " << v9.is_collinearity(v20) << endl;
        cout << "Scalar multiplication {5, 5} and {10, 0}: " << v9 * v10 << endl << endl;

        Vector<int> v11(4, 1, 0, 0, 0);
        cout << "Is vector of length one? {4, 1, 0, 0, 0}: " << v11.is_single() << endl;
        cout << "Are two vectors equal? {3, 4, 0} and {3, 4, 0}: " << (v3 == v6) << endl;
        cout << "Are two vectors not equal? {3, 4, 0} and {3, 4, 0}: " << (v3 != v6) << endl;

    }
    catch (baseError& err)
    {
        cout << err.what() << endl;
    }
    return 0;
}
