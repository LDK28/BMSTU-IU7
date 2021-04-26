import random
count = int(input('Count = '))
try:
    f = open('my_data_' + str(count) + '.txt', 'w')
    f.write(str(count) + '\n')
    for i in range(count):
        f.write(str(random.randint(-1000, 1000)) + ' ')
    f.close()
except Exception as ex:
    print(ex)