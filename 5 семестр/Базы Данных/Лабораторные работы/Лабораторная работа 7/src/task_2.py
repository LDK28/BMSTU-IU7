from lawyer import *
import json
import psycopg2

from colors import *


def connection():
    con = None
    # Подключаемся к БД.
    try:
        con = psycopg2.connect(
            database="lab_1",
            user="postgres",
            password="281001",
            host="localhost",  # Адрес сервера базы данных.
            port="5432"  # Номер порта.
        )
    except:
        print("Ошибка при подключении к БД")
        return con

    print("База данных успешно открыта")
    return con


def output_json(array):
    print(BLUE)
    for elem in array:
        print(json.dumps(elem.get()))
    print(YELLOW)


def read_table_json(cur, count=15):
    # Возвращает массив кортежей словарей.
    cur.execute("SELECT * FROM lawyers_json")
    rows = cur.fetchmany(count)

    array = list()
    for elem in rows:
        tmp = elem[0]
        # print(elem[0], sep=' ', end='\n')
        array.append(lawyer(tmp['id'], tmp['name'], tmp['email_address'], tmp['phone_number'],
                          tmp['skill'], tmp['office_address'], tmp['process_count']))

    print(GREEN)
    for elem in array:
        print(elem.get())

    return array


def update_lawyer(lawyers, in_id):
    for elem in lawyers:
        if elem.id == in_id:
            print(BLUE, elem.get())
            elem.skill += 1
            print(GREEN, elem.get())


def add_lawyer(lawyers, lawyer):
    lawyers.append(lawyer)
    output_json(lawyers)


def task_2():
    con = connection()
    # Объект cursor используется для фактического
    # выполнения наших команд.
    cur = con.cursor()

    # 1. Чтение из XML/JSON документа.
    print(GREEN, f'{"1.Чтение из XML/JSON документа:":^130}')
    lawyers_array = read_table_json(cur)
    # 2. Обновление XML/JSON документа.
    print(BLUE, f'\n{"2.Обновление XML/JSON документа:":^130}')
    update_lawyer(lawyers_array, 3)
    # 3. Запись (Добавление) в XML/JSON документ.
    print(YELLOW, f'{"3.Запись (Добавление) в XML/JSON документ:":^130}')
    add_lawyer(lawyers_array, lawyer(1111, 'Dmitry', 'qq@mqil.qu', '+79149141414', 9, 'addressius', 123))

    # Закрываем соединение с БД.
    cur.close()
    con.close()

task_2()