#   Лабораторна работа №14

#   Назначение программы:
#       Определение наличия гласных латинских букв в каждой строке символьной
#       матрицы и при их наличии размещение в начало строки, а все другие в
#       конец. Строки, имеющие гласные записать в один файл, не имеющтие -
#       в другой.

#   Назначение переменных:
#       R - матрица
#       L, M - размеры матрицы
#       i, j, l, k, d - счётчики
#       f, g - файлы

#   Текстовый пример:
#       b  a  u
#       d  t  g
#       q  r  e
#     Вывод:
#       a  u  b
#       d  t  g
#       e  q  r
#     Файл glasn:
#       a  u  b
#       e  q  r
#     Файл neglasn:
#       d  t  g


def procedure(R,L,M):
#   Постановка гласных в начала строк
    s = 'eEyYuUiIoOaA'
    for i in range(L):
        l = 0
        for j in range(M):
            if R[i][j] in s:
                R[i].insert(l, R[i].pop(j))
                l += 1
#   Запись файлов
    try:
        f = open('glasn.txt', 'w')
        k = 0
        for i in range(L):
            for j in range(M):
                if R[i][0] in s:
                    f.write(R[i][j] + ' ')
                    k = 1
            if k == 1:
                f.write('\n')
        f.close()
    except:
        print('Ошибка записи файлa glasn!')
            
    try:
        g = open('neglasn.txt', 'w')
        k = 0
        for i in range(L):
            for j in range(M):
                if R[i][0] not in s:
                    g.write(R[i][j] + ' ')
                    k = 1
            if k == 1:
                g.write('\n')

        g.close()
    except:
        print('Ошибка записи файлa neglasn!')


def main():
    L = int(input('Введите количество строк матрицы: '))
    M = int(input('Введите количество столбцов матрицы: '))
    R = [[0]*M for i in range(L)]
    print('Введите элементы матрицы, по одному в строке:')
    for i in range (L):
        print(i+1,'строка')
        for j in range(M):
            R[i][j] = input()
            while len(R[i][j]) > 1:
                print('!!Размер элемента не должен превышать 1!!')
                R[i][j] = input('Введите элемент повторно: ')

    print('Исходная матрица:')
    for i in R:
        print(i)
            
    procedure(R,L,M)

    print('\nПреобразованная матрица')
    for i in R:
        print(i)

    #   Вывод содержимого файлов
    try:
        print('\nСодержимое файла(glasn.txt), содержащего строки с гласными:')
        f = open('glasn.txt', 'r')
        if (f.readline() == ''):
            print('файл пуст')
        else:
            f.seek(0,0)
            for line in f:
                print(line, end = '')
        f.close()
    except:
            print('Файла f не существует!')
            
    try:
        print('\nСодержимое файла(neglasn), не содержащего строки с гласными:')
        g = open('neglasn.txt', 'r')
        if (g.readline() == ''):
            print('файл пуст')
        else:
            g.seek(0,0)
            for line in g:
                print(line, end = '')
        g.close()
    except:
            print('Файла g не существует!')


if __name__ == '__main__':
    main()
