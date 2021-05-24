class Differentiator(object):
    @staticmethod
    def __none_check(value: float):
        return 0 if value is None else value

    @staticmethod
    def __left_inter(y: float, yl: float, h: float) -> float:
        return (y - yl) / h

    @staticmethod
    def left(y: list[float], h: float) -> list[float]:
        res = []

        for i in range(len(y)):
            res.append(None if i == 0
                       else Differentiator.__left_inter(y[i], y[i - 1], h))

        return res

    @staticmethod
    def center(y: list[float], h: float) -> list[float]:
        res = []

        for i in range(len(y)):
            res.append(None if i == 0 or i == len(y) - 1
                       else (y[i + 1] - y[i - 1]) / 2 * h)

        return res

    @staticmethod
    def second_runge(y: list[float], h: float, p: float) -> list[float]:
        res, y2h = [], []
        for i in range(len(y)):
            y2h.append(0.0 if i < 2 else (y[i] - y[i - 2]) / (2. * h))

        yh = Differentiator.left(y, h)
        for i in range(len(y)):
            res.append(None if i < 2
                       else
                       Differentiator.__none_check(yh[i]) +
                       (
                               Differentiator.__none_check(yh[i]) -
                               Differentiator.__none_check(y2h[i])
                       ) / (2.0 ** p - 1))

        return res

    @staticmethod
    def aligned_coeffs(x: list[float], y: list[float]) -> list[float]:
        res = []
        for i in range(len(y)):
            res.append(None if i == len(y) - 1
                       else
                       y[i] * y[i] / x[i] / x[i] *
                       Differentiator.__left_inter(
                           -1. / y[i + 1], -1. / y[i],
                           -1. / x[i + 1] - -1. / x[i]
                       ))

        return res

    @staticmethod
    def second_left(y: list[float], h: float) -> list[float]:
        res = []
        for i in range(len(y)):
            res.append(None if i == 0 or i == len(y) - 1
                       else (y[i - 1] - 2 * y[i] + y[i + 1]) / (h * h))

        return res

    @staticmethod
    def print_init(txt: str, init: list[float]):
        print(txt)

        for i in init:
            print("{:7.4} ".format(i if i is not None else "none"))

        print()

    @staticmethod
    def print_res(txt: str, res: list[float]):
        print(txt)

        for i in res:
            print("{:7.4} ".format(i if i is not None else "none"))

        print()
