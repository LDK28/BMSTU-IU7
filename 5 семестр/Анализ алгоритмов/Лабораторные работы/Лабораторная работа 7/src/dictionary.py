from color import *

INPUT_KEY = True


def create_dictionary(db_file_name):
    try:
        f_db = open(db_file_name, "r")
    except:
        print("%s\nОшибка открытия файла с базой данных! %s"
            %(red, base_color))

    db = f_db.read()
    db = db.split("\n")

    f_db.close()

    for i in range(len(db)):
        db[i] = db[i].split(", ")

    dictionary = dict()

    for row in db:
        dictionary[row[0]] = row[1:]

    return dictionary
    

def print_dict_field(key, data, numb_comparisons):
    data_str = data[0] + ", " + data[1] + ", " + data[2]

    print("%s\nКлюч: %s%s\n%sИнформация: %s%s\n%sКол-во сравнений: %s%d"
        %(green, base_color, key, 
          green, base_color, data_str,
          green, base_color, numb_comparisons))


def search_in_dictionary(dictionary, alg):
    if INPUT_KEY:
        key = input("%s\nВведите фамилию клиента: %s" %(blue, base_color))
    else:
        key = "Ковалец"

    res = alg(key, dictionary)

    if res is not None:
        print_dict_field(key, res[0], res[1])
    else:
        print("%s\nТакого клиента в базе данных не найдено :(%s"
            %(red, base_color))


def sort_dict_by_key(dictionary):
    keys = list(dictionary.keys())
    keys.sort()

    sorted_dict = dict()

    for key in keys:
        sorted_dict[key] = dictionary[key]

    return sorted_dict


def sort_dict_by_data(dictionary):
    data = list(dictionary.items())
    data.sort(key = lambda d: d[1], reverse = True)

    sorted_dict = dict()

    for row in data:
        sorted_dict[row[0]] = row[1]

    return sorted_dict


def segment_dict(dictionary):
    tmp_dict = {i: 0 for i in "ЙЦУКЕНГШЩЗХФЫВАПРОЛДЖЭЁЯЧСМИТБЮ"}

    for key in dictionary:
        tmp_dict[key[0]] += 1

    tmp_dict = sort_dict_by_data(tmp_dict)

    segmented_dict = tmp_dict

    for key in segmented_dict:
        segmented_dict[key] = dict()

    for key in dictionary:
        segmented_dict[key[0]].update({key: dictionary[key]})

    return segmented_dict
