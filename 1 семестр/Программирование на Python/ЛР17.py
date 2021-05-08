#   Лабораторная работа №17

#   Назначение программы:
#       Создание меню для отрывка литературного произведения


text = ['Все счастливые семьи похожи друг на друга, каждая несчастливая',
        'семья несчастлива по-своему. Все смешалось в доме Облонских. Жена',
        'узнала, что муж был в связи с бывшею в их доме',
        'француженкою-гувернанткой, и объявила мужу, что не может жить с ним',
        'в одном доме.  Положение это продолжалось уже третий день и',
        'мучительно чувс-6+4твовалось и самими супругами, и всеми членами семьи,',
        'и домочадцами. Все члены семьи и домочадцы чувствовали, что нет',
        'смысла в их сожительстве и что на каждом постоялом дворе случайно',
        'сошедшиеся люди более связаны между собой, чем они, члены семьи и',
        'домочадцы Облонских.']

choice = None
while choice != '0':
    print(
        '''
------------------------------------------
1 - Выравнивание по ширине
2 - Выравнивание по левому крвю
3 - Выравнивание по правому краю
4 - Замена во всём тексте одного слова другим
5 - Удаление одного слова из текста
6 - Замена арифмитического выражения на результат их вычисления
7 - Реверс строк
0 - Выход из программы
'''
        )
    choice = input('Выбор: ')
    if choice == '0':
        print('Выход')
# 1 Выравнивание по ширине
    elif choice == '1':
        # Удаление лишних пробелов
        for i in range(len(text)):
            s = text[i][0]
            for j in range(1, len(text[i])):
                if text[i][j] == ' ' and text[i][j - 1] == ' ':
                    s += ''
                elif i == len(text[i]) - 1:
                    s += ''
                else:
                    s += text[i][j]
            text[i] = s
            if text[i][0] == ' ':
                s = ''
                for j in range(1, len(text[i])):
                    s += text[i][j]
                text[i] = s

        wide = 0
        for i in range(len(text)):
            if len(text[i]) > wide:
                wide = len(text[i])
        for i in range(len(text)):
            if text[i].count(' ') != 0:
                count_ = int((wide - len(text[i]))/text[i].count(' '))
                remain = (wide - len(text[i]) - count_*text[i].count(' '))
            else:
                count_ = wide - len(text[i])
                remain = 0
            s = ''
            for j in range(len(text[i])):
                if text[i][j] != ' ':
                    s += text[i][j]
                else:
                    s += ' '*(count_ + 1)
                    if remain > 0:
                        s += ' '
                        remain -= 1

            text[i] = s
        for a in text:
            print(a)
        
                

# 2 Выравнивание по левому краю 
    elif choice == '2':
        for i in range(len(text)):
            s = text[i][0]
            for j in range(1, len(text[i])):
                if text[i][j] == ' ' and text[i][j - 1] == ' ':
                    s += ''
                elif i == len(text[i]) - 1:
                    s += ''
                else:
                    s += text[i][j]
            text[i] = s
            if text[i][0] == ' ':
                s = ''
                for j in range(1, len(text[i])):
                    s += text[i][j]
                text[i] = s

        for a in text:
            print(a)

# 3 Выравнивание по правому краю
    elif choice == '3':
        # Удаление лишних пробелов
        for i in range(len(text)):
            s = text[i][0]
            for j in range(1, len(text[i])):
                if text[i][j] == ' ' and text[i][j - 1] == ' ':
                    s += ''
                elif i == len(text[i]) - 1:
                    s += ''
                else:
                    s += text[i][j]
            text[i] = s
            if text[i][0] == ' ':
                s = ''
                for j in range(1, len(text[i])):
                    s += text[i][j]
                text[i] = s

            
        wide = 0
        for i in range(len(text)):
            if len(text[i]) > wide:
                wide = len(text[i])
        for i in range(len(text)):
            count_ = (wide - len(text[i]))
            text[i] = ' '*count_ + text[i]
        for a in text:
            print(a)
        

# 4 Замена во всём тексте одного слова другим
    elif choice == '4':
        signs = ',.!?:;'
        word_incorrect = input('Введите заменяемое слово: ')
        word_correct = input('Введите новое слово: ')
        for i in range(len(text)):
            text[i] = ' ' + text[i] + ' '
            if  ' ' + word_incorrect + ' ' in text[i]:
                text[i] = text[i].replace(' ' + word_incorrect + ' ' , ' ' + word_correct + ' ')
            for j in signs:
                if  ' ' + word_incorrect + j in text[i]:
                    text[i] = text[i].replace(' ' + word_incorrect + j , ' ' + word_correct + j)
            text[i] = text[i][1:len(text[i])-1]
        for a in text:
            print(a)
        
# 5 Удаление одного слова из текста
    elif choice == '5':
        signs = ',.!?:;'
        word = input('Введите слово: ')
        for i in range(len(text)):
            text[i] = ' ' + text[i] + ' '
            if  ' ' + word + ' ' in text[i]:
                text[i] = text[i].replace(' ' + word + ' ' , ' ')
            for j in signs:
                if  ' ' + word + j in text[i]:
                    text[i] = text[i].replace(' ' + word + j , j)
            text[i] = text[i][1:len(text[i])-1]
        for a in text:
            print(a)
        

# 6 Замена арифмитического выражения на результат их вычисления
    elif choice == '6':
        numbers = '1234567890'
        for i in range(len(text)):
            for j in range(len(text[i])):
                if text[i][j] == '+' or text[i][j] == '-':
                    s_left = ''
                    s_right = ''
                    pos_left = j - 1
                    while pos_left >= 0 and text[i][pos_left] in numbers:
                        s_left = text[i][pos_left] + s_left
                        pos_left -= 1
                    if s_left != '':
                        pos_right = j + 1
                        while pos_right < len(text[i]) and text[i][pos_right] in numbers:
                            s_right += text[i][pos_right]
                            pos_right += 1
                        if s_right != '':
                            if text[i][pos_left] == '-':
                                s_left = text[i][pos_left] + s_left
                                pos_left -= 1
                            # Проверка на float
                            check_float = 0
                            if text[i][pos_left] == '.' and text[i][pos_left - 1] in numbers:
                                check_float = 1
                                s_left = text[i][pos_left] + s_left
                                pos_left -= 1
                                while pos_left >= 0 and text[i][pos_left] in numbers:
                                    s_left = text[i][pos_left] + s_left
                                    pos_left -= 1
                            if s_left != '':
                                if check_float == 0:
                                    if text[i][j] == '+':
                                        Str = str(int(s_left) + int(s_right))
                                    if text[i][j] == '-':
                                        Str = str(int(s_left) - int(s_right))
                                else:
                                    if text[i][j] == '+':
                                        Str = str(float(s_left) + float(s_right))
                                    if text[i][j] == '-':
                                        Str = str(float(s_left) - float(s_right))
                                if pos_right != len(text[i]):
                                    text[i] = ' '*(pos_right - pos_left - 1 - len(Str)) +\
                                        text[i][:pos_left + 1] + Str + \
                                        text[i][pos_right:]
                                else:
                                    text[i] = ' '*(pos_right - pos_left - 1 - len(Str)) +\
                                        text[i][:pos_left + 1] + Str

        # Выравнивание
        for i in range(len(text)):
            s = text[i][0]
            for j in range(1, len(text[i])):
                if text[i][j] == ' ' and text[i][j - 1] == ' ':
                    s += ''
                elif i == len(text[i]) - 1:
                    s += ''
                else:
                    s += text[i][j]
            text[i] = s
            if text[i][0] == ' ':
                s = ''
                for j in range(1, len(text[i])):
                    s += text[i][j]
                text[i] = s
        for a in text:
            print(a)




    elif choice == '7':
        for i in range(len(text)):
            text[i] = text[i][::-1]
            print(text[i])

                

    else:
        print('\n!Введённого номера нет!')
