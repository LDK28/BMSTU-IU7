#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <functional>
#include <math.h>

using namespace std;

constexpr double EPS = 1e-8;

double R0 = 0.35;
double Tw = 2e3;
double T0 = 1e4;
double k0 = 0.0008;
double c = 3e10;
int p = 4;

double T(double z)
{
    return (Tw - T0) * pow(z, p) + T0;
}

double k(double z)
{
    double tmp = T(z) / 300.;
    return k0 * tmp * tmp;
}

double up(double z)
{
    return (3.084 * 1e-4) / (exp(47990. / T(z)) - 1);
}

struct Range
{
    double start;
    double stop;
    double step;

    Range(double _start, double _stop, double _step) : start(_start), stop(_stop), step(_step)
    {
    }
};

struct triplet
{
    double f, s, t;

    triplet(double x, double y, double z) : f(x), s(y), t(z) {}

    double operator[](int i) const
    {
		double result;
        switch (i)
        {
        case 0:
            result = f;
        case 1:
            result = s;
        case 2:
            result = t;
        }
		return result;
    }
};

vector<double> solve_matrix(const std::vector<triplet> &mat, const vector<double> &vec)
{
    vector<double> ksi, eta;

    int n = mat.size() - 1;

    ksi.push_back(0.0);
    eta.push_back(0.0);

    ksi.push_back(-mat[0][1] / mat[0][0]);
    eta.push_back(vec[0] / mat[0][0]);

    for (int i = 1; i < mat.size() - 1; i++)
    {
        double a = mat[i][0];
        double b = -mat[i][1];
        double c = mat[i][2];

        ksi.push_back(c / (b - a * ksi[i]));
        eta.push_back((-vec[i] + a * eta[i]) / (b - a * ksi[i]));
    }

    vector<double> res;
    res.push_back((vec[n] - mat[n][1] * eta[n]) / (mat[n][1] * ksi[n] + mat[n][2]));
    for (int i = 0; i < n; i++)
    {
        res.push_back(res[i] * ksi[n - i] + eta[n - i]);
    }

    for (int i = 0; i < res.size() / 2; i++)
    {
        std::swap(res[i], res[res.size() - 1 - i]);
    }

    return res;
}

double K(double z)
{
    return c / (3. * k(z));
}

double P(double z)
{
    return c * k(z);
}

double F(double z)
{
    return -c * k(z) * up(z);
}

double X(double z, double h)
{
    return (K(z) + K(z + h)) / 2.;
}

double V(double z, double h)
{
    double tmp1 = (z - h / 2.) * (z - h / 2.);
    double tmp2 = (z + h / 2.) * (z + h / 2.);
    return (tmp2 - tmp1) / 2;
}

std::pair<vector<triplet>, vector<double>> dif_scheme(const Range &range)
{
    vector<triplet> triplets;
    vector<double> res;

    double z = range.start;
    double h = range.step;

    triplets.push_back(triplet(-1. / R0 / R0 / h * X(z, h) * (z + h / 2.) - h / 4. * V(z + h / 4., h / 2.) * (P(z) + 1 / 2. * P(z + h / 2)),
                               1. / R0 / R0 / h * X(z, h) * (z + h / 2.) - h / 8. * V(z + h / 4., h / 2.) * P(z + h / 2.),
                               0));
    res.push_back(((F(z) + F(z + h / 2.)) * h * V(z + h / 4., h / 2.) / 4.));

    for (z += h; z < range.stop - h / 2.; z += h)
    {
        double A = (z - h / 2.) * X(z - h, h) / (R0 * R0 * h);
        double C = (z + h / 2.) * X(z, h) / (R0 * R0 * h);

        triplets.push_back(triplet(A, -(A + C + P(z) * V(z, h)), C));
        res.push_back(F(z) * V(z, h));
    }

    triplets.push_back(
        triplet(0,
                (z - h / 2.) * X(z - h, h) / (R0 * R0 * h) - h * V(z - h / 4., h / 2.) * P(z - h / 2.) / 8.,
                -(z - h / 2.) * X(z - h, h) / (R0 * R0 * h) - z * 0.393 * c / R0 - h / 4. * V(z - h / 4., h / 2.) * (P(z - h / 2.) / 2. + P(z))));
    res.push_back(
        h / 4. * (F(z - h / 2.) + F(z)) * V(z - h / 4., h / 2.));

    return std::pair<vector<triplet>, vector<double>>(triplets, res);
}

vector<double> solve_eq(const Range &range)
{
    std::pair<vector<triplet>, vector<double>> tmp = dif_scheme(range);
    return solve_matrix(tmp.first, tmp.second);
}

std::pair<vector<double>, vector<double>> deriative(const vector<double> &u, const Range &range)
{
    vector<double> res;
    vector<double> res2;

    double z = range.start;

    res.push_back(0.0);
    res2.push_back(0.0);

    for (int i = 1; i < u.size() - 1; i++, z += range.step)
    {
        res.push_back(-c / 3 / R0 / k(z) * ((u[i + 1] - u[i - 1]) / 2. / range.step));
        res2.push_back(-c / 3 / R0 / k(z) * (u[i + 1] + u[i - 1] - 2. * u[i]) / range.step / range.step);
    }

    res.push_back(-c / 3 / R0 / k(z) * (-4 * u[u.size() - 2] + u[u.size() - 3] + 3 * u[u.size() - 1]) / 2. / range.step);
    res2.push_back(*res2.rbegin());

    res2[0] = res2[1];

    return make_pair(res, res2);
}

double simpsonIntegral(double a, double b, int n, const std::function<double(double)> &f)
{
    const double width = (b - a) / (n - 1);

    double simpson_integral = 0;
    for (int step = 0; step < (n - 1) / 2; step++)
    {
        const double x1 = a + 2 * step * width;
        const double x2 = a + 2 * (step + 1) * width;

        simpson_integral += (f(x1) + 4 * f((x1 + x2) / 2.) + f(x2));
    }

    return simpson_integral * width / 3;
}

void print_table(ostream &stream, const std::vector<vector<double>> &res, const Range &range)
{
    cout << "u     F"
         << "\n";

    double cur = range.start;

    for (int i = 0; i < res[0].size(); i++)
    {
        stream << res[0][i] << " " << up(res[0][i]) << " " << res[1][i] << " " << res[2][i] << " " << res[3][i] << "\n";
        cur += range.step;
    }
}

void integr(const vector<double> &u, const vector<double> &F, const Range &range)
{

    cout << "Integration result: " << c * R0 * simpsonIntegral(range.start, range.stop, (range.stop - range.start) / range.step, [&](double x)
                                                               {
           // cout << int(x / range.step) << "\n";
            return k(x) * (up(x) - u[int(x / range.step)]) * x; });
}

int main()
{
    // vector<triplet> test{ {1, 2, 0}, {3 ,4 ,5}, {0, 2, 7} };
    // vector<double> test2{ 2, 2, 8 };
    //
    // vector<double> res = solve_matrix(test, test2);
    //
    // for (const auto& elem : res)
    //{
    //     std::cout << elem << "\n";
    // }

    Range range(0.0, 1.0, 1e-4);

    vector<double> z;
    for (double i = range.start; i < range.stop; i += range.step)
    {
        z.push_back(i);
    }

    vector<double> u = solve_eq(range);
    std::pair<vector<double>, vector<double>> F = deriative(u, range);

    double x = 0.0;

    ofstream str("res.txt");
    print_table(str, std::vector<vector<double>>({z, u, F.first, F.second}), range);
    str.close();

    integr(u, F.first, range);

    // system("/bin/python3 \"/home/ldk/Рабочий стол/BMSTU-IU7/6 семестр/Моделирование/Лабораторная работа 3/graph.py\"");
    // system("python graph.py");
    system("C:/Python310/python.exe c:/Users/1/Desktop/mod/m3/graph.py");

    return 0;
}
