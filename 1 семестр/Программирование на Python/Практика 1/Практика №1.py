#   Практикум №1

#   Назначение программы:
#       Нахождение во входном файле всех palinwords и вывод их в другой
#       текстовый файл по одному в строке

#   Назначение переменных:
#       filein, fileout - переменные входново и выходного файлов соответственно
#       count - счётчик палиндромов в текущем palinword
#       str1, str2 - строки, для хранения встречающихся палиндромов в
#                данной строке символов
#       line, List, word - впомогательные переменные для считывания и проверки
#                    строк файла
#       i, j - счётчики
#       check - счётчик palinwords

#   Текстовый пример:
#       Input.txt:
#           MOEILIJKHEDEN INVOER
#           VERNEDEREN
#           AMUMA AMAMA MUMMUM
#           DUMMY
#       Output.txt:
#           MOEILIJKHEDEN
#           VERNEDEREN
#           AMAMA
#           MUMMUM

def main():
#   Проверка на открытие файлов
    try:
        filein = open('Input.txt', 'r')
    except Exception as ex:
        print(ex)
        return False

    try:
        fileout = open('Output.txt', 'w')
    except Exception as ex:
        print(ex)
        filein.close()
        return False

    check = 0
    for line in filein:
#   Разделение текущей строки по пробелам
        if line[-1] == '\n':
            line = line[:-1]
        List = line.split(' ')
        for word in List:
            count = 0
            str1 = ''
            str2 = ''
#   Проверка на количество палиндромов(k) в текущей строке символов
            for j in range(1, len(word)-2):
                if word[j-1] == word[j+2] and word[j] == word[j+1]:
                    if (word[j-1] + word[j] + word[j+1] + word[j+2])\
                        not in str2:
                        count += 1
                        str2 += (word[j-1] + word[j] + word[j+1] + word[j+2])\
                                 + ' '
            for j in range(len(word)-2):
                if word[j] == word[j+2]:
                    if (word[j] + word[j+1] + word[j+2]) not in str1 and\
                       (word[j] + word[j+1] + word[j+2]) not in str2:
                        count += 1
                        str1 += (word[j] + word[j+1] + word[j+2]) + ' '
            if count > 1:
                fileout.write(word + '\n' + '    Встреченные палиндромы: ' + str1 + str2 + '\n')
                check = 1
    if check == 0:
        fileout.write('В исходном файле не встречено palinwords')
    filein.close()
    fileout.close()


main()
