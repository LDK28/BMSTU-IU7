import matplotlib.pyplot as plt


def gen_label(n, m, md1, md2) -> str:
    f1s = "Gauss" if md1 == 0 else "Simpson"
    f2s = "Gauss" if md2 == 0 else "Simpson"

    return "N = {:}, M = {:}, Methods = {:}-{:}".format(n, m, f1s, f2s)


def plot(fs, sc, ns, ms, md1s, md2s):
    plt.clf()

    plt.title("Integration using meansquare method")
    plt.xlabel("Tao")
    plt.ylabel("Result")
    plt.grid(which='minor', color='k', linestyle=':')
    plt.grid(which='major', color='k')

    for i in range(len(fs)):
        x, y = [], []
        j = sc[0]
        while j < sc[2]:
            x.append(j)
            y.append(fs[i](j))
            j += sc[1]

        plt.plot(x, y, label=gen_label(ns[i], ms[i], md1s[i], md2s[i]))

    plt.legend()
    plt.savefig('points.png')
    plt.show()
