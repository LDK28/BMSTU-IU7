#   Лабораторная работа №16

#   Назначение программы:
#       Работа с набором записей одинаковой структуры, находящемся в файле
#       с помощью меню

#   Назначение переменных:
#       f - файл
#       l - строка для записей
#       s, s1, s2 - строки для поиска по полю
#       choice - команда

choice = None
while choice != '0':
    print(
        '''
------------------------------------------
1 - Выбор файла
2 - Создание в файле нового набора записей
3 - Добавление записей
4 - Вывод всех записей
5 - Поиск по одному полю
6 - Поиск по двум полям
0 - Выход из программы
'''
        )
    choice = input('Выбор: ')
    if choice == '0':
        print('Выход')
# 1
    elif choice == '1':
        file = input('Введите название файла: ') + '.txt'
# 2
    elif choice == '2':
        try:
            f = open(file, 'w')
            n = int(input('Введите количество наборов записей: '))
            while n < 1:
                print('!!Неверный ввод!!\n')
                n = int(input('Введите значение повторно: '))
            print('Введите наборы, каждый с новой строки, поля разделяйте'\
                  ' пробелами:')
            for i in range(n):
                l = input()
                while len(l.split(' ')) != 3:
                    print('!!Неверное количество полей(3 поля)!!\n')
                    l = input('Введите значение повторно: ')
                f.write(l + '\n')
            f.close()
        except Exception as ex:
            print(ex)
# 3
    elif choice == '3':
        try:
            f = open(file, 'a')
            n = int(input('Введите количество наборов записей: '))
            while n < 1:
                print('!!Неверный ввод!!\n')
                n = int(input('Введите значение повторно: '))
            print('Введите наборы, каждый с новой строки, поля разделяйте'\
                  ' пробелами:')
            for i in range(n):
                l = input()
                while len(l.split(' ')) != 3:
                    print('!!Неверное количество полей(3 поля)!!\n')
                    l = input('Введите значение повторно: ')
                f.write(l + '\n')
            f.close()
        except Exception as ex:
            print(ex)
# 4
    elif choice == '4':
        try:
            f = open(file)
            for line in f:
                print(line, end = '')
            f.close()
        except Exception as ex:
            print(ex)
# 5     
    elif choice == '5':
        try:
            i1 = int(input('Введите номер столбца поля: ')) - 1
            s = input('Введите поле: ')
            f = open(file)
            print('')
            k = 0
            for line in f:
                sl = (line[:len(line)-1].split(' '))
                if s == sl[i1]:
                    k += 1
                    if k == 1:
                        print('Найденые записи:')
                    print(line, end = '')
            if k == 0:
                print('По заданым критериям записей не найдено')
            f.close()
        except Exception as ex:
            print(ex)
# 6
    elif choice == '6':
        try:
            i1 = int(input('Введите номер столбца поля 1: ')) - 1
            s1 = input('Введите поле: ')
            i2 = int(input('Введите номер столбца поля 2: ')) - 1
            s2 = input('Введите поле: ')
            f = open(file)
            print('')
            k = 0
            for line in f:
                sl = (line[:len(line)-1].split(' '))
                if s1 == sl[i1] and s2 == sl[i2]:
                    k += 1
                    if k == 1:
                        print('Найденые записи:')
                    print(line, end = '')
            if k == 0:
                print('По заданым критериям записей не найдено')                
            f.close()
        except Exception as ex:
            print(ex)
    else:
        print('\n!Введённого номера нет!')
