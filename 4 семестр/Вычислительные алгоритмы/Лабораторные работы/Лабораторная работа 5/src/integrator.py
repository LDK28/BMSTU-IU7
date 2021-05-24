from math import cos, sin, exp, pi
from scipy.special import roots_legendre
from typing import Callable as Call


class Integrator(object):
    def __init__(self, lm: list[list[float]], n: list[int], fn: list[int]):
        self.lm = lm
        self.n = n
        self.f1 = Integrator.simpson if (fn[0]) else Integrator.gauss
        self.f2 = Integrator.simpson if (fn[1]) else Integrator.gauss

    def __call__(self, p: float) -> float:
        f = Integrator.__integrated(p)

        inner = lambda x: self.f2(
            lambda val1: f(x, val1),
            self.lm[1][0],
            self.lm[1][1],
            self.n[1])
        integ = lambda: self.f1(
            inner,
            self.lm[0][0],
            self.lm[0][1],
            self.n[0])

        return integ()

    @staticmethod
    def __integrated(p: float) -> Call[[float, float], float]:
        t = lambda x, y: 2 * cos(x) / (1 - sin(x) ** 2 * cos(y) ** 2)
        return lambda x, y: 4 / pi * (1 - exp(-p * t(x, y))) * cos(x) * sin(x)

    @staticmethod
    def simpson(f: Call[[float], float], a: float, b: float,
                n: int) -> float:
        if n < 3 or n % 2 == 0:
            raise Exception("Sorry, wrong n value")

        h = (b - a) / (n - 1.0)
        x = a
        res = 0.0

        for i in range((n - 1) // 2):
            res += f(x) + 4 * f(x + h) + f(x + 2 * h)
            x += 2 * h

        return res * h / 3

    @staticmethod
    def gauss(f: Call[[float], float], a: float, b: float,
              n: int) -> float:
        def p2v(p: float, c: float, d: float) -> float:
            return (d + c) / 2 + (d - c) * p / 2

        x, w = roots_legendre(n)
        return sum([(b - a) / 2 * w[i] * f(p2v(x[i], a, b)) for i in range(n)])
