import numpy


def f(x):
    return x * x


def values():
    print("Enter start, end and step separated by a space:")

    start, stop, step = map(float, input().split())
    x_values = numpy.arange(start, stop + 0.1, step)
    y_values = [f(x) for x in x_values]

    return x_values, y_values


def print_table(x_values, y_values):
    print(" {:^10} {:^10}".format("X", "Y"))
    for i in range(len(x_values)):
        print("|{:^10} |{:^10}|".format(
            round(x_values[i], 4), round(y_values[i], 4)))


def find_min(x_values, x):
    for i in range(len(x_values) - 1):
        if x > x_values[i] and x < x_values[i + 1]:
            return i


def interpolation(x_values, y_values, x):
    n = len(x_values)
    index = find_min(x_values, x)
    if not index:
        print("The value is either present in the table or is outside of it")
        return

    h = [0]
    for i in range(1, n):
        h.append(x_values[i] - x_values[i - 1])

    A = [0, 0]
    for i in range(2, n):
        A.append(h[i - 1])

    B = [0, 0]
    for i in range(2, n):
        B.append(-2 * (h[i - 1] + h[i]))

    D = [0, 0]
    for i in range(2, n):
        D.append(h[i])

    F = [0, 0]
    for i in range(2, n):
        F.append(-3 * ((y_values[i] - y_values[i - 1]) / h[i] -
                       (y_values[i - 1] - y_values[i - 2]) / h[i - 1]))

    # Прямой ход.
    E = [0 for i in range(n + 1)]
    η = [0 for i in range(n + 1)]
    for i in range(2, n):
        E[i + 1] = D[i] / (B[i] - A[i] * E[i])
        η[i + 1] = (A[i] * η[i] + F[i]) / (B[i] - A[i] * E[i])

    # Обратный ход.
    c = [0 for i in range(n + 1)]
    for i in range(n - 2, -1, -1):
        c[i] = E[i + 1] * c[i + 1] + η[i + 1]

    a = [0]
    for i in range(1, n):
        a.append(y_values[i - 1])

    b = [0]
    for i in range(1, n):
        b.append((y_values[i] - y_values[i - 1]) /
                 h[i] - h[i] / 3 * (c[i + 1] + 2 * c[i]))

    d = [0]
    for i in range(1, n):
        d.append((c[i + 1] - c[i]) / (3 * h[i]))

    diff = x - x_values[index - 1]
    return a[index] + b[index] * (diff) + c[index] * ((diff) ** 2) + d[index] * ((diff) ** 3)


def main():
    x_values, y_values = values()

    print_table(x_values, y_values)

    x = float(input("Enter x: "))

    result = interpolation(x_values, y_values, x)
    if not result:
        return

    print("f({}) = {}".format(x, f(x)))
    print("Interpolation spline: {}".format(round(result, 4)))
    print("Error = {}".format(abs(round(f(x) - result, 4))))


if __name__ == "__main__":
    main()
