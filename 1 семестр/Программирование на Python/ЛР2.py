# Лабораторная работа №2

# Назначение программы: нахождение объёма, площади поверхности, радиусов
# описанной и вписанной сфер икосаэдра по заданной длине ребра

# Обозначение переменных:
# a - длина ребра икосаэдра
# V - объём икосаэдра
# S - площадь поверхности икосаэдра
# R - радиус описанной сферы
# r - радиус вписанной сферы

# текстовый пример
# при вводе 10 программа должна вывести:
# V = 2181.695;  S = 866.025;  R = 9.511;  r = 7.558

a=float(input('Длина стороны икосаэдра a = '))
if a<=0:
    print('Неверные данные')
else:
    V=5*a**3*(3+5**0.5)/12
    S=5*a**2*3**0.5
    R=a*(2*(5+5**0.5))**0.5/4
    r=a*(3+5**0.5)/(4*3**0.5)
    print('Объём икосаэдра V = {:.3f}\nПлощадь поверхности икосаэдра S = {:.3f}\
\nРадиус описанной сферы R = {:.3f}\nРадиус вписанной сферы\
 r = {:.3f}'.format(V,S,R,r))
