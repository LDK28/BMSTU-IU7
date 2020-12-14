import random

filename = input("Input filename: ")
count = int(input("Input count of students: "))

f = open(filename, 'w')

names = ['Dmitry', 'Petr', 'Maxim', 'Diana', 'Maria', 'Ekaterina', 'Inakenty', 'Arseny']
surnames = ['Ivanov', 'Petrov', 'Sidorov', 'Pirozhkov', 'Kovalev', 'Gromov']
streets = ['Pobedy', 'Baumana', 'Gomelskovo', 'Zheleznodorozhnaya', 'Komsomolskaya']

f.write(str(count) + '\n\n\n')
for i in range(count):
    f.write(random.choice(names) + '\n')
    f.write(random.choice(surnames) + '\n')
    f.write(random.choice(['0', '1']) + '\n')
    f.write(str(random.randint(16, 45)) + '\n')
    f.write(str(random.randint(1, 7)) + '\n')
    f.write(str(random.randint(2, 5)) + '\n')
    f.write(str(random.randint(2012, 2020)) + '\n')
    house = random.choice(['0', '1'])
    f.write(house + '\n')
    if house == '0':
        f.write(random.choice(streets) + '\n')
        f.write(str(random.randint(1, 20)) + '\n')
        f.write(str(random.randint(1, 120)) + '\n')
    elif house == '1':
        f.write(str(random.randint(1, 10)) + '\n')
        f.write(str(random.randint(1,60)) + '\n')
    f.write('\n')
    

f.close()
print("File created!")