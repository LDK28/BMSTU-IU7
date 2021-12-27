from color import *
from alg_search import *
from dictionary import sort_dict_by_key, segment_dict


MSG = "\n\t\t%sМеню\n\n"\
      "\t1. Полный перебор \n"\
      "\t2. Бинарный поиск \n"\
      "\t3. Поиск сегментами \n"\
      "\t4. Замеры времени \n"\
      "\t5. Провести анализ кол-ва сравнений \n"\
      "\t0. Выход \n\n"\
      "\tВыбор: %s"\
      %(yellow, base_color)

ALG = "\n\t\t%sВыбор алгоритма\n\n"\
      "\t1. Полный перебор \n"\
      "\t2. Бинарный поиск \n"\
      "\t3. Поиск сегментами \n\n"\
      "\tВыбор: %s"\
      %(blue, base_color)


def read_menu():
    try:
        menu = int(input(MSG))
    except:
        menu = -1
    
    if menu < 0 or menu > 5:
        print("%s\nОжидался ввод целого числа от 0 до 5 %s"
            %(red, base_color))

    return menu


def read_alg(dictionary):
    try:
        menu = int(input(ALG))
    except:
        menu = -1

    if menu == 1:
        return full_search, "Полный перебор", dictionary

    elif menu == 2:
        return binary_search, "Бинарный поиск", sort_dict_by_key(dictionary)
        
    elif menu == 3:
        return segment_search, "Поиск сегментами", segment_dict(sort_dict_by_key(dictionary))

    else:
        print("%s\nОжидался ввод целого числа от 0 до 3 %s" %(red, base_color))

