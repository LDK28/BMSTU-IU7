# -*- coding: utf-8 -*-
import math
from unicodedata import name
import pylab

def function(x, y):
    return x ** 2 + y ** 2 # функция первой производной

def picar1(x):
    return x**3  

def picar2(x):
    return picar1(x) + x ** 7  

def picar3(x):
    return picar2(x) + (x ** 11) * (2 / 2079) + (x ** 15) / 59535
    
def picar4(x):
    return picar3(x) + (x ** 15)*(2 / 93555) + (x ** 19)*(2 / 3393495) + (x ** 19)*(2 / 2488563) + \
    (x ** 23)*(2 / 86266215) + (x ** 23)*(1 / 99411543) + (x ** 27)*(2 / 3341878155) + (x ** 31)*(1 / 109876902975)

def Euler(n, h, x, y):
    answer = []
    
    for i in range(n):
        try:
            y += h * function(x, y)
            answer.append(y)   
            x += h
        except OverflowError:
            answer.append("Over")
            
    return answer

def rungeKutta(n, h, x, y, alpha = 0.5):
    answer = []

    for i in range(n):
        try:
            step1 = (1 - alpha) * function(x, y)
            step2 = alpha * function(x + h / (2 * alpha), y + (h / (2 * alpha)) * function(x, y))
            step3 = step1 + step2
            y += h * step3
            answer.append(y)   
            x += h
        except OverflowError:
            answer.append("Over")
            
    return answer 


def checkFormat(item):
    if type(item) == float:
        if item > 1000000:
            return '{:.4e}'.format(item)
        return '{:.4f}'.format(item)
    
    elif type(item) == int:
        return str(item)
    else:
        return item

def get_graphics(y1, y2, y3, y4,y5, y6, xlist):
    pylab.xlabel('x')
    pylab.ylabel('u(x)')
    pylab.plot(xlist, y1, label = "1-e приближение Пикара")
    pylab.plot(xlist, y2, label = "2-e приближение Пикара")
    pylab.plot(xlist, y3, label = "3-e приближение Пикара")
    pylab.plot(xlist, y4, label = "4-e приближение Пикара")
    pylab.plot(xlist, y5, label = "Метод Эйлера")
    pylab.plot(xlist, y6, label = "Метод Рунге-Кутта")
    pylab.legend(loc='upper left')
    pylab.title("График функции")
    pylab.show()

def main():
    x_start = 0
    xst = -2
    x_end = 2
    
    h = 1e-5

    n = math.ceil(abs(x_end - x_start) / h) + 1 # число итераций
    
    n2 = math.ceil(abs(xst - x_start) / h) + 1 # число итераций
    output_step2 = int(n2 / 15000)
    output_step = int(n / 200) # выводим только 200 значений в таблице



    
    while 1:
        print("___________________Меню____________________")
        print("1. Таблица")
        print("2. График")
        print("3. Выйти")
        print("")
        c = 0
        while True:
            try:
                c = int(input("Выберите пункт: "))
                if c > 3 or 1 > c:
                    raise Exception()
                break
            except Exception as e:
                print('Неверный формат')
        print()
        if c == 1:
            answer_euler = Euler(n, h, 0, 0)
            answer_rungeKutta = rungeKutta(n, h, 0, 0)
            print("------------------------------------------------------------------------------------------------------------")
            print("|         |__________________________Метод Пикара_________________________|    Метод     |      Метод      |")
            print("|    x    |               |               |               |               |    Эйлера    |   Рунге-Кутты   |")
            print("|         |   1-е прибл.  |   2-е прибл.  |   3-е прибл.  |   4-е прибл.  |              |                 |")
            print("------------------------------------------------------------------------------------------------------------")
    
            for i in range(0, n, output_step):
                print("|{:^9.2f}|{:^15.2f}|{:^15.2f}|{:^15.2f}|{:^15.2f}|{:^14s}|{:^17s}|".format(x_start, picar1(x_start), picar2(x_start), \
                                                                                     picar3(x_start), picar4(x_start), \
                                                                                     checkFormat(answer_euler[i]), checkFormat(answer_rungeKutta[i])))
                x_start += h * output_step
        
            
            print()
        elif c == 2:
            answer_euler1 = Euler(n, h, 0, 0)
            #print(answer_euler1)
            #print()
            answer_euler2 = Euler(n, -h, 0, 0)
            answer_euler2.reverse()
            res_euler = answer_euler2 + answer_euler1

                
            answer_rungeKutta1 = rungeKutta(n, h, 0, 0)
            answer_rungeKutta2 = rungeKutta(n, -h, 0, 0)
            answer_rungeKutta2.reverse()
            res_rungeKutta = answer_rungeKutta2 + answer_rungeKutta1

            for i in range(0, n, output_step):
                print(res_rungeKutta[i])
                print()
            
            xlist = []
            ypicar1 = []
            ypicar2 = []
            ypicar3 = []
            ypicar4 = []
            yeuler = []
            yrungekutta = []
            for i in range(0, 2*n, output_step):
                #print(answer_euler[i])
                #print()
                xlist.append(xst)
                ypicar1.append(picar1(xst))
                ypicar2.append(picar2(xst))
                ypicar3.append(picar3(xst))
                ypicar4.append(picar4(xst))
                yeuler.append(res_euler[i])
                yrungekutta.append(res_rungeKutta[i])
                xst += h * output_step
            #print(xlist)
            get_graphics(ypicar1, ypicar2, ypicar3, ypicar3, yeuler, yrungekutta, xlist)
            print()
        elif c == 3:
            break
if __name__ == "__main__":
    main()
