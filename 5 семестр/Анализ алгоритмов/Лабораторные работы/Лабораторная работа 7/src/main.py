from generate import *
from dictionary import *
from alg_search import *
from read import read_menu
from compare import compare_time, compare_comparsion


def main():
    menu = -1

    dictionary = create_dictionary("../data/db.csv")

    while menu != 0:
        menu = read_menu()

        if menu == 1:
            search_in_dictionary(dictionary, full_search)
        elif menu == 2:
           search_in_dictionary(sort_dict_by_key(dictionary), binary_search)
        elif menu == 3:
            search_in_dictionary(segment_dict(sort_dict_by_key(dictionary)), segment_search)
        elif menu == 4:
            compare_time()
        elif menu == 5:
            compare_comparsion()


if __name__ == "__main__":
    main()
