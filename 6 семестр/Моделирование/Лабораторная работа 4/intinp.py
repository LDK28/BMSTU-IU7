from typing import Tuple
import math
import params
import numpy as np

def fn_k(T: float) -> float:
    return params.conductivity(T)

def fn_c(T: float) -> float:
    return params.capacity(T)

def fn_p(x: float) -> float:
    return 2 / params.R * params.alpha(x)

def fn_f(x: float, t: float, T: float) -> float:
    k = params.absorption(T)
    return k * params.radiation_pulse(t) * math.exp(-k * x) + 2 * params.T0 / params.R * params.alpha(x)

# kappa_{n-1/2}
def kappa(T_nm1: float, T_n: float) -> float:
    k_nm1 = fn_k(T_nm1)
    k_n = fn_k(T_n)
    return 2 * k_nm1 * k_n / (k_nm1 + k_n)

def solve_tridiag(A: Tuple, B: Tuple, C: Tuple, D: Tuple)-> Tuple:
    N = len(A) - 1
    ksi = [0, C[0] / B[0]]
    eta = [0, D[0] / B[0]]
    for n in range(1, N + 1):
        div = (B[n] - A[n] * ksi[n])
        ksi.append(C[n] / div)
        eta.append((D[n] + A[n] * eta[n]) / div)
    X = [None] * (N + 1)
    X[N] = (D[N] + A[N] * eta[N]) / (B[N] - A[N] * ksi[N])
    for n in range(N-1, -1, -1):
        X[n] = ksi[n+1] * X[n+1] + eta[n+1]
    return tuple(X)

def make_tridiag(X: Tuple, t: float, T: Tuple, T_hat: Tuple, h: float, tau: float):
    N = len(X) - 1
    h2 = h * h
    F0 = -params.alpha_0 * (T_hat[0] - params.T0)
    FN = params.alpha_N * (T_hat[-1] - params.T0)

    A0 = 0
    C0 = 2 * kappa(T_hat[0], T_hat[1]) * tau
    B0 = C0 + (fn_p(X[0]) * tau + fn_c(T_hat[0])) * h2
    D0 = (fn_c(T_hat[0]) * T[0] + fn_f(X[0], t, T_hat[0]) * tau) * h2 + 2 * F0 * tau * h

    AN = 2 * kappa(T_hat[N-1], T_hat[N]) * tau
    CN = 0
    BN = AN + (fn_p(X[N]) * tau + fn_c(T_hat[N])) * h2
    DN = (fn_c(T_hat[N]) * T[N] + fn_f(X[N], t, T_hat[N]) * tau) * h2 - 2 * FN * tau * h

    A = (A0,) + tuple(kappa(T_hat[n-1], T_hat[n]) * tau for n in range(1, N)) + (AN,)
    C = (C0,) + tuple(kappa(T_hat[n], T_hat[n+1]) * tau for n in range(1, N)) + (CN,)
    B = (B0,) + tuple(An + Cn + fn_c(Tn) * h2 + fn_p(xn) * tau * h2 for xn, Tn, An, Cn in zip(X[1:-1], T_hat[1:-1], A[1:-1], C[1:-1])) + (BN,)
    D = (D0,) + tuple(fn_f(xn, t, Thatn) * tau * h2 + fn_c(Thatn) * Tn * h2 for xn, Tn, Thatn in zip(X[1:-1], T[1:-1], T_hat[1:-1])) + (DN,)

    return A, B, C, D

def get_max_diff(X1: Tuple, X2: Tuple) -> float:
    return max(abs(x1 - x2) / x1 for x1, x2 in zip(X1, X2))

def relaxation(X1: Tuple, X2: Tuple, factor: float) -> Tuple:
    return tuple(x1 + factor * (x2 - x1) for x1, x2 in zip(X1, X2))

def solve():
    h = params.l / params.N
    tau = params.t_max / params.M
    X = np.linspace(0, params.l, params.N + 1)
    t = np.linspace(0, 4 * params.t_max, params.M)
    T = (params.T0,) * (params.N + 1)
    layers = [T]
    for tm in t:
        T = layers[-1]
        T_hat = T
        max_diff = math.inf
        max_iters = 100
        iters = 0
        while max_diff > 1e-6 and iters < max_iters:
            T_next = solve_tridiag(*make_tridiag(X, tm, T, T_hat, h, tau))
            max_diff = get_max_diff(T_hat, T_next)
            T_hat = relaxation(T_hat, T_next, 0.125)
            iters += 1
        layers.append(T_hat)
    
    return dict(X=X, t=t, layers=layers)

if __name__ == "__main__":
    import seaborn as sb
    import matplotlib.pyplot as plt

    sol = solve()
    for layer in sol["layers"]:
        sb.lineplot(x=sol["X"], y=layer)

    plt.show()
