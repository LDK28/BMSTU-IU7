from interface import *
from SQL import *

import psycopg2
from psycopg2 import Error


def main():
    # Подключаемся к БД.
    status = False
    try:
        database = SQLighter('postgres', '****', 'localhost', '5432', 'lab_1')
        if database.connection:
            status = True

        print("База данных успешно открыта")

        # Интерфейс.
        menu = -1
        while (menu != 0):
            info_show()
            menu = int(input('Выбор: '))

            if menu == 1:
                print("Получение среднего значения скилла юристов:\n")
                avg_skill = database.get_avg_skill()[0][0]
                print("Результат запроса:")
                print(avg_skill)
                input('Для продолжения намите Enter\n')
            if menu == 2:
                print("Получениеданных юристов с датами процессов и id клиентов:\n")
                table = database.get_lawyers_judge_dates()
                print("Результат запроса:")
                for line in table:
                    print(line)
                input('Для продолжения намите Enter\n')
            if menu == 3:
                print("Получениеданных количества ближайших процессов юристов:\n")
                table = database.get_lawyers_judge_count()
                print("Результат запроса:")
                for line in table:
                    print(line)
                input('Для продолжения намите Enter\n')
            if menu == 4:
                print("Получение метаданных столбцов таблицы юристов:\n")
                table = database.get_lawyers_meta()
                print("Результат запроса:")
                for line in table:
                    print(line)
                input('Для продолжения намите Enter\n')
            if menu == 5:
                print("Вызов функции из 3 ЛР(Получение скилла юриста по id):\n")
                id = input("Введите скилл юриста: ")
                print("Результат запроса:")
                print(database.get_lawyers_skill_l3(id)[0][0])
                input('Для продолжения намите Enter\n')
            if menu == 6:
                print("Вызов функции из 3 ЛР(Получение всех данных юриста по id):\n")
                id = input("Введите скилл юриста: ")
                table = database.get_lawyers_l3(id)
                print("Результат запроса:")
                for line in table:
                    print(line)
                input('Для продолжения намите Enter\n')
            if menu == 7:
                print("Вызов функции из 3 ЛР(Вставка юриста).\n")
                database.insert_lawyers_l3()
                print("Результат запроса:\n"
                      "Был вставлен юрист с данными(100, 'Valteri', 'valera@mail.com', '+79443893838', 9, 'Boston', 1000)")
                input('Для продолжения намите Enter\n')

            if menu == 8:
                print("Получение системных данных(текущая таблица и текущий пользователь).\n")
                table = database.get_system_info()
                print("Результат запроса:")
                for line in table:
                    print(line)
                input('Для продолжения намите Enter\n')
            if menu == 9:
                print("Создание таблицы юрист и количество дел.\n")
                database.get_system_info()
                print("Результат запроса:\n"
                      "Была создана таблица lawyer_count_process с полями(id, name, judge_count)")
                input('Для продолжения намите Enter\n')
            if menu == 10:
                print("Вставка юриста.\n")
                database.insert_lawyer()
                print("Результат запроса:\n"
                      "Был вставлен юрист с данными(99, 'Valteri', 'valera@mail.com', '+79443893838', 9, 'Boston', 1000)")
                input('Для продолжения намите Enter\n')

    except (Exception, Error) as error:
        print("Ошибка при работе с PostgreSQL", error)
    finally:
        if status:
            database.cursor.close()
            database.connection.close()
            print("Соединение с PostgreSQL закрыто")


if __name__ == "__main__":
    main()