# Лабораторная работа №3

#   Назначение программы:
# Определение длин сторон треугольника по заданным координатам точек.
# А также нахождение биссектрисы, проведённой из наименьшего угла;
# определение, является ли треугольник прямоугольным;
# определение, находится ли точка с заданными координатами в треугольнике,
# если находится, то определение расстояния от этой точки до ближайшей стороны

# xA - координата точки A по оси абсцисс
# yA - координата точки A по оси ординат
# xB -координата точки B по оси абсцисс
# yB - координата точки B по оси ординат
# xC -координата точки C по оси абсцисс
# yC - координата точки C по оси ординат
# AB - длина стороны AB
# BC - длина стороны BC
# AC - длина стороны AC
# cosA - косинус угла BAC
# cosB - косинус угла ABC
# cosC - косинус угла ACB
# m - вспомогательная переменная для нахождения наибольших и наименьших велечин
# a, b, c - вспомогательные переменные, обозначения сторон
# Bis - биссектриса, проведённая из наименьшего угла
# xT - координата точки для проверки по оси абсцисс
# yT - координата точки для проверки по оси ординат
# R_AB - расстояние от точки для проверки до стороны AB
# R_BC - расстояние от точки для проверки до стороны BC
# R_AC - расстояние от точки для проверки до стороны AC

#   Текстовый пример:
# xA = 1
# yA = 1
# xB = 1
# yB = 4
# xC = 8
# yC = 1
# AB = 3
# BC = 7.616
# AC = 7
# Bis = 7.146
# Данный треугольник - прямоугольный
# xT = 2
# yT = 2
# Данная точка находится в треугольнике ABC
# Расстояние от данной точки до ближайшей стороны =  1.0

# Нахождение сторон треугольниа
xA = int(input('Координата x точки A: '))
yA = int(input('Координата y точки A: '))
xB = int(input('Координата x точки B: '))
yB = int(input('Координата y точки B: '))
xC = int(input('Координата x точки C: '))
yC = int(input('Координата y точки C: '))
AB = ((xA - xB)**2 + (yA - yB)**2)**0.5
BC = ((xB - xC)**2 + (yB - yC)**2)**0.5
AC = ((xA - xC)**2 + (yA - yC)**2)**0.5
if (AB+BC<AC) or (AB+AC<BC) or (BC+AC<AB):
    print('Такого треугольника не существует')
else:
    print('Длина стороны AB = ''{:.3f}'.format(AB))
    print('Длина стороны BC = ''{:.3f}'.format(BC))
    print('Длина стороны AC = ''{:.3f}'.format(AC))

# Нахождение длины биссектрисы, проведённой из наименьшего угла
    cosA = ((AB**2 + AC**2 - BC**2) / (2*AB*AC))
    cosB = ((AB**2 + BC**2 - AC**2) / (2*AB*BC))
    cosC = ((BC**2 + AC**2 - AB**2) / (2*BC*AC))
    m = cosA
    a = AB
    b = AC
    c = BC
    if cosB>m:
        m = cosB
        a = AB
        b = BC
        c = AC
    if cosC>m:
        m = cosC
        a = AC
        b = BC
        c = AB
    Bis = (a*b*(a + b + c)*(a + b - c))**0.5 / (a + b)
    print('Длина биссектрисы, проведённой из наименьшего угла = ''{:.3f}\
    '.format(Bis))
 
# Определение типа треугольника
    if (abs(cosA)<1.691768418476429e-15) or (abs(cosB)<1.691768418476429e-15) \
       or (abs(cosC)<1.691768418476429e-15): 
        print('Данный треугольник - прямоугольный')
    else:
        print('Данный треугольник - не прямоугольный')

# Oпределение, находится ли точка с заданными координатами в треугольнике
    xT=int(input('Координата х точки для проверки : '))
    yT=int(input('Координата y точки для проверки : '))
    if ((xT>xA and xT<xB) or (xT>xA and xT<xC) or (xT>xB and xT<xA) or \
       (xT>xB and xT<xA) or (xT>xC and xT<xA) or (xT>xC and xT<xB)) and\
       ((yT>yA and yT<yB) or (yT>yA and yT<yC) or (yT>yB and yT<yA) or \
       (yT>yB and yT<yA) or (yT>yC and yT<yA) or (yT>yC and yT<yB)):
        print('Данная точка находится в треугольнике ABC')
# Определение расстояния от данной точки до ближайшей стороны
        R_AB = (abs((yB - yA)*xT - (xB - xA)*yT + xB*yA - yB*yA)) / AB
        R_BC = (abs((yC - yB)*xT - (xC - xB)*yT + xC*yB - yC*yB)) / BC
        R_AC = (abs((yA - yC)*xT - (xA - xC)*yT + xA*yC - yA*yC)) / AC
        print('Расстояние от данной точки до ближайшей стороны = ',\
                      round(min(R_AB,R_BC,R_AC),3))
    else:
        print('Данная точка не лежит в треугольнике ABC')
