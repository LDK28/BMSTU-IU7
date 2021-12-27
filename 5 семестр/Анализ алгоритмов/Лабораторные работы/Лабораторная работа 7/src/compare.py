from time import process_time
import matplotlib.pyplot as plt
from copy import deepcopy

from alg_search import *
from color import *
from generate import generate_db_comparison_file
from dictionary import create_dictionary, sort_dict_by_key, segment_dict
from read import read_alg


TIMES = 1000


def get_process_time(func, key, dictionary):
    time_res = 0

    for _ in range(TIMES):
        time_start = process_time()
        func(key, dictionary)
        time_end = process_time()

        time_res += time_end - time_start

    return time_res / TIMES


def build_graph_time(index_arr, full_search_time, binary_search_time, segment_search_time):

    fig1 = plt.figure(figsize = (10, 7))
    plot = fig1.add_subplot()
    
    plot.plot(index_arr, full_search_time,    label = "Полный перебор")
    plot.plot(index_arr, binary_search_time,  label = "Бинарный поиск")
    plot.plot(index_arr, segment_search_time, label = "Поиск сегментами")

    plt.legend()
    plt.grid()
    plt.title("Измерение времени")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Индекс ключа")
    
    plt.show()
    

def print_measurement_res(index_arr, full_search_time, binary_search_time, segment_search_time):

    print("\n%s  Инд. ключа | Полный перебор | Бинарный перебор | Поиск сегментами\n" 
            "--------------------------------------------------------------------%s"
        %(purple, base_color))

    for ind in range(0, len(index_arr) + 1, 500):
        print("  %6d     %s|%s %12.4e   %s|%s  %12.4e    %s|%s %12.4e " \
            %(ind,                     purple, base_color, 
              full_search_time[ind],   purple, base_color,
              binary_search_time[ind], purple, base_color,
              segment_search_time[ind]))


def compare_time():
    # generate_db_comparison_file("../data/db_comparison.csv")
    dictionary = create_dictionary("../data/db_comparison.csv")
    
    full_search_time    = []
    binary_search_time  = []
    segment_search_time = []

    index_arr = [i for i in range(len(dictionary))]

    keys = list(dictionary.keys())

    steps = 0
    all_steps = len(keys)
    old_percentage = 0

    for key in keys:
        steps += 1

        full_search_time.append(get_process_time(full_search, key, dictionary))
        binary_search_time.append(get_process_time(binary_search, key, sort_dict_by_key(dictionary)))
        segment_search_time.append(get_process_time(segment_search, key, segment_dict(sort_dict_by_key(dictionary))))

        percentage = steps / all_steps * 100
      
        if percentage // 1 > old_percentage:
            old_percentage = percentage

            print("Выполнено: %5.2f%s" %(percentage, "%"))

    print_measurement_res(index_arr, full_search_time, binary_search_time, segment_search_time)
    build_graph_time(index_arr, full_search_time, binary_search_time, segment_search_time)


def build_graph_comparsion(index_arr, cnt_comparsions, cnt_comparsions_sorted, text_alg):
    fig, ax = plt.subplots(2, 1, figsize = (10, 7))

    ax[0].bar(index_arr, cnt_comparsions, alpha = 0.5, color = "green")
    ax[0].set(title = text_alg)
    ax[0].set_ylabel("Количество сравнений")
    ax[0].grid()

    ax[1].bar(index_arr, cnt_comparsions_sorted, alpha = 0.5)
    ax[1].set(title = text_alg + " (отсоритрованный)")
    ax[1].set_xlabel("Индекс ключа")
    ax[1].set_ylabel("Количество сравнений")
    ax[1].grid()

    plt.show()
    
    
def compare_comparsion():
    dictionary = create_dictionary("../data/db_comparison.csv")

    keys = list(dictionary.keys())

    index_arr = [i for i in range(len(dictionary))]

    alg, text_alg, dictionary = read_alg(dictionary)
    
    if alg is None:
        return

    cnt_comparsions = []
 
    percentage = 0
    all_percentage = len(keys)

    for key in keys:
        percentage += 1

        cnt_comparsions.append(alg(key, dictionary)[1])

        perc_completion = percentage / all_percentage * 100

        if perc_completion % 1 == 0:
            print("Выполнено: %5.2f%s" %(perc_completion, "%"))

    cnt_comparsions_sorted = deepcopy(cnt_comparsions)
    cnt_comparsions_sorted.sort(reverse = True)

    build_graph_comparsion(index_arr, cnt_comparsions, cnt_comparsions_sorted, text_alg)
    