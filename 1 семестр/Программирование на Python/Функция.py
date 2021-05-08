# Лабораторная работа №5

# Назначение программы: нарисовать график функции

# start - начальное значение a
# finish - конечное значение а
# step - шаг изменения аргумента
# Ras - количество засечек
# l - длина строки на вывод
# C,a - значение функции и её аргумент соответсвенно
# Cmax,Cmin - максимальное и минимальное значения функции соответственно
# delta = Cmax - Cmin
# Zas,lenth - вспомогательные переменные

start = float(input('Введите начальное значение аргумента а: '))
finish = float(input('Введите конечное значение аргумента а: '))
step = float(input('Введите шаг изменения аргумента: '))
Ras = int(input('Введите количество засечек: '))-1

l = 100
a = start
Zas = round((l)/Ras)
lenth = 0

# Нахождение Cmin и Cmax
Cmin = Cmax = a**7 - a**6 + 8*a**5 - 4*a**4 + 6*a**3 + 2*a**2 - 5*a + 1
for k in range(abs(round((finish-start)/step))):
    C = a**7 - a**6 + 8*a**5 - 4*a**4 + 6*a**3 + 2*a**2 - 5*a + 1
    if C < Cmin:
        Cmin = C
    if C> Cmax:
        Cmax = C
    a+=step
delta = Cmax - Cmin
K = Cmin+delta/Ras
# Вывод значений в засечках
for i in range(l+9):
    if i < 7:
        print(' ', end = '')
    elif i == 7:
        if abs(Cmin) >= 1000:
            print('{:<9.2e}'.format(Cmin), end = '')
            lenth+=10
        elif abs(Cmin) <= 0.0001:
            print('{:<9.2e}'.format(Cmin), end = '')
            lenth+=10
        else:
            print('{:<6.2f}'.format(Cmin), end = '')
            lenth+=7
    elif (i == l+7-lenth) or (i == l+6-lenth):
        print(' ', end = '')
    elif i == l+9-lenth:
        if abs(Cmax) >= 1000:
            print('{:<9.2e}'.format(Cmax))
        elif abs(Cmin) <= 0.0001:
            print('{:<9.2e}'.format(Cmax), end = '')
            lenth+=10
        else:
            print('{:<6.2f}'.format(Cmax))
        break
    elif (i-9+lenth)%Zas == 0:
            if abs(K) >= 1000:
                print('{:<9.2e}'.format(K), end = '')
                lenth+=8
                K+=delta/Ras
            elif abs(K) <= 0.0001:
                print('{:<9.2e}'.format(K), end = '')
                lenth+=8
                K+=delta/Ras
            else:
                print('{:<7.2f}'.format(K), end = '')
                lenth+=6
                K+=delta/Ras
    else:
        print(' ', end = '')

Zas = round((l)/Ras)

# Построение оси с
for i in range (l+10):
    if i < 8:
        print(' ', end = '')
    elif i == (abs(round((0-Cmin)/delta*l))+8) and Cmin<0:
        print(chr(9516), end = '')
    elif (i == l+7) or (i == l+6):
        print(chr(9472), end = '')
    elif i == 8:        
        print(chr(9492), end = '')
    elif i == l+8:
        print(chr(9496), end = '')
    elif i == l+9:
        print('c')
        break
    elif (i-8)%Zas == 0:
        print(chr(9524), end = '')
    else:
        print(chr(9472), end = '')

a = start
# Построение графика
for j in range(abs(round((finish - start)/step+1))):
    C = a**7 - a**6 + 8*a**5 - 4*a**4 + 6*a**3 + 2*a**2 - 5*a + 1
    for i in range(l+3):

# Вывод значений аргумента
        if i == 0:
            if abs(a)<0.000001:
                a = 0
            if abs(a) >= 1000:
                print('{:<8.1e}'.format(a), end = '')
            else:
                print('{:<8.2f}'.format(a), end = '')

# Построение точек графика
        elif i == abs(round((C-Cmin)/delta*l))+1:
            print('*', end = '')

# Построение оси a
        elif Cmin < 0 and i == (abs(round((0-Cmin)/delta*l))+1):
            if j == abs(round((finish - start)/step)):
                print('a', end = '')
            else:
                print(chr(9474), end = '')
        elif i == l+2:
            print('')
        else:
            print(' ', end = '')
    a+=step
