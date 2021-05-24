from differentiator import Differentiator


def main():
    x = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
    y = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]
    h = 1.0

    Differentiator.print_init("X              :", x)
    Differentiator.print_init("Y              :", y)
    Differentiator.print_res("Onesided       :", Differentiator.left(y, h))
    Differentiator.print_res("Center         :",
                             Differentiator.center(y, h))
    Differentiator.print_res("Second Runge   :",
                             Differentiator.second_runge(y, h, 1))
    Differentiator.print_res("Aligned params :",
                             Differentiator.aligned_coeffs(x, y))
    Differentiator.print_res("Second onesided:",
                             Differentiator.second_left(y, h))


if __name__ == "__main__":
    main()
