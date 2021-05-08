# Лабораторная работа №3(задача 14)

# Назначение программы:
# Расчёт значений функции

# Обозначение переменных:
# start - начальное значение аргумента а
# step - шаг изменения аргумента
# end - конечное значение аргумента
# ma, mi - максимальное и минимальное значения с соответственно
# l - количество значений с
# delta - разница между максимальным и минимальным значениями функции

# Контрольные точки:
# a = 0.5   c = -0.2578
# a = 0.1   c = 0.5257

start = float(input('Введите начальное значение аргумента: '))
end = float(input('Введите конечное значение аргумента: '))
step = float(input('Введите шаг изменения аргумента: '))
l = int(abs(end - start)/step)
a = start
ma = mi = a**7 - a**6 + 8*a**5 - 4*a**4 + 6*a**3 + 2*a**2 - 5*a + 1

# Построение верхней границы таблицы
for i in range(24):
    if i == 0:
        print(chr(9484), end = '')
    elif i == 23:
        print(chr(9488))
    elif i == 10:
        print(chr(9516), end = '')
    else:
        print(chr(9472), end = '')
print('│{:^9s}│{:^12s}│'. format('a', 'c'))
for i in range(24):
    if i == 0:
        print(chr(9500), end = '')
    elif i == 23:
        print(chr(9508))
    elif i == 10:
        print(chr(9532), end = '')
    else:
        print(chr(9472), end = '')


# Вычисление функции и её печать
for i in range(l + 1):
    c = a**7 - a**6 + 8*a**5 - 4*a**4 + 6*a**3 + 2*a**2 - 5*a + 1
    if c < mi:
        mi = c
    if c > ma:
        ma = c
    if abs(c) > 10000:
        print('│{:^9.2f}│{:^12.4e}│'.format(a,c))
    else:
         print('│{:^9.2f}│{:^12.4f}│'.format(a,c))
# Построение границ таблицы
    if i < l:
            for i in range(24):
                if i == 0:
                    print(chr(9500), end = '')
                elif i == 23:
                    print(chr(9508))
                elif i == 10:
                    print(chr(9532), end = '')
                else:
                    print(chr(9472), end = '')
# Построение нижней границы таблицы
    else:
        for i in range(24):
                if i == 0:
                    print(chr(9492), end = '')
                elif i == 23:
                    print(chr(9496))
                elif i == 10:
                    print(chr(9524), end = '')
                else:
                    print(chr(9472), end = '')
    a+=step
    
# Вычисление разности между максимальным и минимальным значениями функции
delta = ma - mi
print('Cmax - Cmin = ''{:.4e}'.format(delta))
