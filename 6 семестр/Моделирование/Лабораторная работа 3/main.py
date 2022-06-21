# -*- coding: utf-8 -*-

from math import e

import numpy as np
from matplotlib import pyplot as plt
from prettytable import PrettyTable

k_0 = 0.018  # 0.018
m = 0.786
R = 0.35
T_w = 2000
T_0 = 10000
c = 3e10
p = 4
STEP_RK = 1e-4
z_max = 1
z_min = 0
EPS = 1e-6


def T(z):
    return (T_w - T_0) * (z**p) + T_0


def k(z):
    return k_0 * ((T(z) / 300) ** 2)


def u_p(z):
    return 3.084e-4 / (e ** (4.799e4 / T(z)) - 1)


def U_z(z, f):
    return -(3 * R * f * k(z)) / c


def F_z(z, f, u):
    if abs(z - 0) < 1e-4:
        return ((R * c) / 2) * k(z) * (u_p(z) - u)
    else:
        return R * c * k(z) * (u_p(z) - u) - (f / z)


def divF(z, u):
    return c * k(z) * (u_p(z) - u)


def k_n(z):
    return c / (3 * R * k(z))


def half_kappa(z):
    return (k_n(z + STEP_RK / 2) + k_n(z - STEP_RK / 2)) / 2


def f_n(z):
    return c * k(z) * u_p(z)


def p_n(z):
    return c * k(z)


def A(z):
    return (z - STEP_RK / 2) * (half_kappa(z - STEP_RK / 2))


def C(z):
    return (z + STEP_RK / 2) * half_kappa(z + STEP_RK / 2)


def B(z):
    return A(z) + C(z) + p_n(z) * z * STEP_RK**2 * R


def D(z):
    return f_n(z) * z * STEP_RK**2 * R


###########################Краевые условия###############################

# При х = 0
def left_bound_cond(z0, h):
    K0 = -half_kappa(z0 + h / 2) * (z0 + h / 2) + c * R * h * h / 8 * k(z0 + h / 2) * (
        z0 + h / 2
    )
    M0 = half_kappa(z0 + h / 2) * (z0 + h / 2) + c * R * h * h / 8 * k(z0 + h / 2) * (
        z0 + h / 2
    )
    P0 = c * R * h * h / 4 * k(z0 + h / 2) * u_p(z0 + h / 2) * (z0 + h / 2)
    return K0, M0, P0


# При x = N
def right_bound_cond(z, h):
    KN = (
        half_kappa(z - h / 2) * (z - h / 2)
        + m * c * z * h / 2
        + c * R * h * h / 8 * k(z - h / 2) * (z - h / 2)
        + R * c * h * h * k(z) / 4
    )
    MN = -half_kappa(z - h / 2) * (z - h / 2) + c * R * h * h / 8 * k(z - h / 2) * (
        z - h / 2
    )
    PN = (
        c
        * R
        * h
        * h
        / 4
        * (k(z - h / 2) * u_p(z - h / 2) * (z - h / 2) + k(z) * u_p(z))
    )
    return KN, MN, PN


########################################################################


def straight():
    h = STEP_RK
    K0, M0, P0 = left_bound_cond(z0=0.0, h=STEP_RK)

    # Прогоночные коэф.
    eps = [0.0, -K0 / M0]
    eta = [0.0, P0 / M0]

    x = h
    n = 1
    while x < z_max:
        eps.append(C(x) / (B(x) - A(x) * eps[n]))
        eta.append((A(x) * eta[n] + D(x)) / (B(x) - A(x) * eps[n]))
        n += 1
        x += h

    return n, eta, eps


def reverse(n, eta, eps):
    kn, mn, pn = right_bound_cond(z=1.0, h=STEP_RK)

    u = [0] * n
    u[n - 1] = (pn - mn * eta[n]) / (kn + mn * eps[n])

    for i in range(n - 2, -1, -1):
        u[i] = eps[i + 1] * u[i + 1] + eta[i + 1]  # /8.001

    return u


def run():
    n, eta, eps = straight()
    u = reverse(n, eta, eps)
    return u


def center_formula(y, z, h):
    res = [(-3 * y[0] + 4 * y[1] - y[2]) / 2 / h]
    for i in range(1, len(y) - 1):
        r = (y[i + 1] - y[i - 1]) / 2 / h
        res.append(r)
    res.append((3 * y[-1] - 4 * y[-2] + y[-3]) / 2 / h)
    return res


def F_res_deriv(u, z):
    f = [0]
    u_res = center_formula(u, z, STEP_RK)
    for i in range(1, len(z)):
        r = -c / 3 / R / k(z[i]) * u_res[i]
        f.append(r)
    return f


def F_res_integ(z, un, un1):
    if abs(z - 1) < 1e-4:
        return m * c * un / 2

    return half_kappa(z - STEP_RK / 2) * (un - un1) / STEP_RK


def render_table(z_res, f_res, f_deriv_res, u_res, div_f):
    tb = PrettyTable()
    tb.add_column("Z", z_res)
    tb.add_column("F", f_res)
    tb.add_column("F deriv", f_deriv_res)
    tb.add_column("U * 1e6", [item * 1e6 for item in u_res])
    tb.add_column("divF", div_f)

    tb.float_format = ".5"

    with open("result.txt", "w") as f:
        f.write(str(tb))


def draw_graph(z_res, f_res, f_deriv_res, u_res, div_f, up_res):
    name = ["U(z)", "F(z)"]
    plt.subplot(2, 2, 1)
    plt.plot(z_res, u_res, "b", label="u")
    plt.plot(z_res, up_res, "k", label="u_p")
    plt.legend()
    plt.title(name[0])
    plt.grid()

    plt.subplot(2, 2, 2)
    plt.plot(z_res, f_res, "r")
    plt.title(name[1])
    plt.grid()

    plt.subplot(2, 2, 3)
    plt.plot(z_res, div_f, "r")
    plt.title("divF")
    plt.grid()
    
    plt.subplot(2, 2, 4)
    plt.plot(z_res, f_deriv_res, "g")
    plt.title("F(z) deriv")
    plt.grid()

    plt.show()


def solve():
    u_res = run()

    z_res = [i for i in np.arange(0, 1 + STEP_RK, STEP_RK)]
    z_res_len = len(z_res)

    f_res, up_res, div_f = [0] * z_res_len, [0] * z_res_len, [0] * z_res_len

    f_deriv_res = F_res_deriv(
        u=u_res,
        z=z_res,
    )

    for i in range(0, len(z_res) - 1):
        up_res[i] = u_p(
            z=z_res[i],
        )
        div_f[i] = divF(
            z=z_res[i],
            u=u_res[i],
        )

    for i in range(1, len(z_res)):
        f_res[i] = F_res_integ(
            z=z_res[i],
            un=u_res[i - 1],
            un1=u_res[i],
        )

    return z_res, f_res, f_deriv_res, u_res, div_f, up_res


def main():
    z_res, f_res, f_deriv_res, u_res, div_f, up_res = solve()
    render_table(z_res, f_res, f_deriv_res, u_res, div_f)
    draw_graph(z_res, f_res, f_deriv_res, u_res, div_f, up_res)


if __name__ == "__main__":
    main()