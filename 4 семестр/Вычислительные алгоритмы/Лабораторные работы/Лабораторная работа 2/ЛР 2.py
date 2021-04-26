# Лабораторная работа №2

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def getIndex(points, x):
    dif = abs(points[0].x - x)
    index = 0
    for i in range(len(points)):
        if abs(points[i].x - x) <= dif:
            dif = abs(points[i].x - x)
            index = i
    return index


def getWorkingPoints(points, index, n):
    left = index
    right = index
    for i in range(n - 1):
        if i % 2 == 0:
            if left == 0:
                right += 1
            else:
                left -= 1
        else:
            if right == len(points) - 1:
                left -= 1
            else:
                right += 1
    return points[left:right + 1]


def Newton(points, x, n):
    index = getIndex(points, x)
    workingPoints = getWorkingPoints(points, index, n)

    vals = [p.y for p in workingPoints]
    args = [p.x for p in workingPoints]
    difs = [vals[0]]
    col_num = len(vals)
    for i in range(1, col_num):
        for j in range(col_num - 1):
            vals[j] = (vals[j] - vals[j + 1]) / (args[j] - args[j + i])
        difs.append(vals[0])
        col_num -= 1

    result = 0
    multiplier = 1
    for i in range(n):
        result += (difs[i] * multiplier)
        multiplier *= (x - args[i])
    return result


def result(x, y, xArray, yArray, table):
    print('\nИнтерполяции таблично заданных функций двух переменных:\n')
    print("|---------------------------------------|")
    print("|         |   nx=1  |   nx=2  |   nx=3  |")
    print("|---------|---------|---------|---------|")
    for ny in range(1, 4):
        print("| ny={:1d}    |".format(ny), end="")
        for nx in range(1, 4):
            args = []
            for i in range(len(table)):
                points = []
                for j in range(len(xArray)):
                    points.append(Point(xArray[j], table[i][j]))
                args.append(Newton(points, x, nx + 1))
            points = []
            for i in range(len(yArray)):
                points.append(Point(yArray[i], args[i]))
            result = Newton(points, y, ny + 1)
            print("{:9.4f}|".format(result), end="")
        print("\n|---------|---------|---------|---------|")


if __name__ == "__main__":
    x = 1.5
    y = 1.5
    xArray = [0, 1, 2, 3, 4]
    yArray = [0, 1, 2, 3, 4]
    table = [[0, 1, 4, 9, 16],
             [1, 2, 5, 10, 17],
             [4, 5, 8, 13, 20],
             [9, 10, 13, 18, 25],
             [16, 17, 20, 25, 32]]
    result(x, y, xArray, yArray, table)
