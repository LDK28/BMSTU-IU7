#   Лабораторная работа №13

#   Назначение программы:
#       Создать новый файл f, в котором сначала будут записаны нечётные строки
#       из файла g, а затем чётные

#   Название переменных:
#       g, f - текстовые файлы
#       k - счётчик строк

g = open('g.txt')
f = open('f.txt','w')

k = 1
for line in g:
    if k%2:
        f.write(line)
    k += 1
f.write('\n')
g = open('g.txt')
f = open('f.txt','a')

k = 1
for line in g:
    if k%2 == 0:
        f.write(line)
    k += 1

f.close()
g.close()
