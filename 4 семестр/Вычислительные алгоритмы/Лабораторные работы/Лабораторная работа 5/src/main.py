from math import pi

import plot
import integrator as inter


def main():
    sc = [0.05, 0.05, 10.0]

    ns, ms = [], []
    md1s, md2s = [], []
    ints = []

    end = '0'
    while end == '0':
        ns.append(int(input("Input N: ")))
        ms.append(int(input("Input M: ")))

        p = float(input("Enter parameter (tao): "))

        md1s.append(
            int(input("Outer integration mode (0 - Gauss, 1 - Simpson): ")))

        md2s.append(
            int(input("Inner integration mode (0 - Gauss, 1 - Simpson): ")))

        lm = [[0, pi / 2], [0, pi / 2]]

        ints.append(
            inter.Integrator(lm, [ns[-1], ms[-1]], [md1s[-1], md2s[-1]]))

        print("Result with {:.2f} as "
              "a parameter is {:.7f}".format(p, ints[-1](p)))

        end = input("Stop execution?: ")

    plot.plot(ints, sc, ns, ms, md1s, md2s)


if __name__ == "__main__":
    main()
