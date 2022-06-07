from numpy import exp


k0 = 1.0
a1 = 0.0134
b1 = 1
c1 = 4.35e-4 
m1 = 1
a2 = 2.049
b2 = 0.563e-3
c2 = 0.528e5
m2 = 1
l = 10
T0 = 300
R = 0.5

alpha_0 = 0.05
alpha_N = 0.01

F_max = 50
t_max = 10

N = 30
M = 20

# lambda(T)
def conductivity(T: float) -> float:
    return a1 * (b1 + c1 * T ** m1)

def conductivity_prime(T: float) -> float:
    return a1 * c1 * m1 * T ** (m1 - 1)

# c(T)
def capacity(T: float) -> float:
    return a2 + b2 * T ** m2 - c2 / T ** 2

# k(T)
def absorption(T: float) -> float:
    return k0 * (T / 300) ** 2

# F_0(t)
def radiation_pulse(t: float) -> float:
    # return F_max / 10
    t_rel = t / t_max
    return F_max * t_rel * exp(1 - t_rel)

def alpha(x: float) -> float:
    d = alpha_N * l / (alpha_N - alpha_0)
    return alpha_0 * d / (d - x)
