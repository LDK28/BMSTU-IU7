import matplotlib.pyplot as plt

file = open("/Users/vladimirprocenko/Desktop/lab04/data.txt", "r")
line = " "
radiuses = []
times = []

while 1:
    line = file.readline()
    if line == '\n':
        break
    radiuses.append(int(line[:-1]))

line = file.readline()
plt.title(line[:-1])

while 1:
    line = file.readline()
    if line == '\n':
        break
    times.append(int(line[:-1]))
plt.plot(radiuses, times, label="Каноническое уравнение")
times = []

while 1:
    line = file.readline()
    if line == '\n':
        break
    times.append(int(line[:-1]))
plt.plot(radiuses, times, label="Параметрическое уравнение")
times = []

while 1:
    line = file.readline()
    if line == '\n':
        break
    times.append(int(line[:-1]))
plt.plot(radiuses, times, label="Алгоритм Брезенхема")
times = []

while 1:
    line = file.readline()
    if line == '\n':
        break
    times.append(int(line[:-1]))
plt.plot(radiuses, times, label="Алгоритм средней точки")
times = []

while 1:
    line = file.readline()
    if line == '\n':
        break
    times.append(int(line[:-1]))
plt.plot(radiuses, times, label="Библиотечная функция")
times = []

plt.legend()

plt.xlabel('Размеры')
plt.ylabel('Время(в миллисекундах)')

plt.grid()
plt.show()