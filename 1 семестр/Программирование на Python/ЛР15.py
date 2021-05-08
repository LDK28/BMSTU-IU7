#       Лабораторная работа №15

#       Назначение программы:
#               Сортировка типизированного файла методом min-max

#       Назначение переменных:
#               p - исходный файл
#               L - количество элементов
#               h - вспомогательный файл
#               i, j, min_i, curent_i - счётчики
#               min_num, curent_num - вспомогательные переменные

#       Текстовый пример:
#               L = 4
#               2  4  6  1
#               Преобразованный файл:
#               1  2  4  6


def Sorting(P):
    try:           
# Подсчёт количества элементов
        p = open(P)
        length = 0
        for i in p:
            length += 1
        p.close()
# Сортировка 
        min_i = 0
        min_num = 0
        curent_i = 0
        curent_num = 0 
        for i in range(length):
            p = open(P)
            curent_i = i
            min_i = i
            for j in range(length):
                a = int(p.readline())
                if j == i:
                    curent_num = a
                    min_num = a
                elif a < min_num and j > i:
                    min_num = a
                    min_i = j
            p.close()
            p = open(P)
            h = open('help.txt', 'w')
            for i in range(length):
                a = int(p.readline())
                if i == min_i:
                    h.write(str(curent_num))
                elif i == curent_i:
                    h.write(str(min_num))
                else:
                    h.write(str(a))
                h.write('\n')
                
            p.close()
            h.close()
# Перезапись
            p = open(P, 'w')
            h = open('help.txt')
            for i in range(length):
                p.write(h.readline())
            p.close()
            h.close()
    except Exception as ex:
        print(ex)


def Data(P):
    try:
        p = open(P,'w')
        L = int(input('Введите количество элементов: '))
        while L > 6 or L < 1:
            if L > 6:
                L = int(input('!!Количество элементов не должно превышать'\
                              ' 6!!\nВведите значение повторно:'))
            if L < 1:
                L = int(input('!!Неверно введено значение!!\n'\
                                'Введите значение повторно: '))
        print('Введите элементы по одному в строке:')
        for i in range(L):
            p.write(input())
            p.write('\n')
        p.close()
    except Exception as ex:
        print(ex)


def Pokaz(P):
    try:
        p = open(P)
        for line in p:
            print(line, end = '')
        p.close()
    except Exception as ex:
        print(ex)



# Основная программа
P = input('Введите название файла: ') + '.txt'
Data(P)
print('\nСодержимое исходного файла:')
Pokaz(P)
Sorting(P)
print('\nСодержимое преобразованного файла:')
Pokaz(P)
