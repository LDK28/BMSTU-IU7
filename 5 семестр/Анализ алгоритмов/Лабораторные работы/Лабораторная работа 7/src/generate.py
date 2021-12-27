from faker import *
from random import randint

NUMBER_ROWS = 3001


def generate_names_surnames_file(name_res_file):
    f_names    = open("../data/names.csv", "r")
    f_surnames = open("../data/surnames.csv", "r")

    names_data    = f_names.read().split("\n")
    surnames_data = f_surnames.read().split("\n")

    f_names.close()
    f_surnames.close()

    res_rows_arr = []
    count_rows = len(surnames_data)

    for i in range(count_rows):
        res_rows_arr.append([surnames_data[i]])

        j = randint(0, len(names_data) - 1)
        res_rows_arr[i].append(names_data[j])

    f_result = open(name_res_file, "w")

    for row in res_rows_arr:
        f_result.write(row[0] + ", " + row[1] + "\n")

    f_result.close()


def generate_db_file(name_res_file):
    f_names = open("../data/names_surnames.csv", "r")

    data = f_names.read().split("\n")

    f_names.close()

    faker = Faker()

    f_db  = open(name_res_file, "w")

    for i in range(len(data)):
        data[i] += ", " + faker.email() + \
                   ", " + faker.phone_number() + "\n"
        
        f_db.write(data[i])

    f_db.close()
        

def generate_db_comparison_file(name_res_file):
    f_db = open("../data/db.csv", "r")
    
    data = f_db.read().split("\n")

    f_db.close()

    f_res  = open(name_res_file, "w")

    for _ in range(NUMBER_ROWS):
        i = randint(0, len(data) - 1)
        f_res.write(data.pop(i) + "\n")

    f_res.close()
