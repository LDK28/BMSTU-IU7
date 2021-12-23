# Variant 4
from datetime import *
from req import *
import psycopg2

#colors
GREEN = '\033[32m'
YELLOW = '\033[33m'
BLUE = '\033[34m'

# Запрсы
FirstQ = """
SELECT DISTINCT fio
FROM employee e 
JOIN employee_check_time ect on e.id = ect.employee_id
WHERE type = 1 AND date = NOW() AND time > '08:00:00' 
AND 
(EXTRACT (HOURS FROM time - '08:00:00') * 60 + EXTRACT (MINUTES FROM time - '08:00:00')) < 5;
"""

SecondQ = """
SELECT fio
FROM employee
"""

ThirdQ = """
SELECT DISTINCT fio
FROM employee e 
JOIN employee_check_time ect on e.id = ect.employee_id
WHERE department = 'Бугхалтерия' AND type = 1 AND time < '08:00:00';
"""

# классы для работы с LINQ
class Employee():
    id = IntegerField(column_name='id')
    fio = CharField(column_name='fio')
    date_of_birth = DateField(column_name='date_of_birth')
    department = CharField(column_name='department')

class EmployeeCheck():
    id = IntegerField(column_name='id')
    employee_id = ForeignKeyField(Employee, backref='employee_id')
    data = DateField(column_name='date')
    day_of_week =  CharField(column_name='day_of_week')
    time = TimeField(column_name='time')
    type = IntegerField(column_name='type')	


class SQLighter:
        def __init__(self, user, password, host, port, database):
            """Подключаемся к БД и сохраняем курсор соединения"""
            self.connection = psycopg2.connect(user=user,
                                                password=password,  # Your PostgreSQL passward
                                                host=host,  # Your DB host
                                                port=port,  # Your PostgreSQL port
                                                database=database)
            self.cursor = self.connection.cursor()

        # task1 SQL
        def task_1_SQL(self):
            with self.connection:
                self.cursor.execute(FirstQ)
                return self.cursor.fetchall()

        # task2 SQL
        def task_2_SQL(self):
            with self.connection:
                self.cursor.execute(SecondQ)
                return self.cursor.fetchall()

        # task3 SQL
        def task_3_SQL(self):
            with self.connection:
                self.cursor.execute(ThirdQ)
                return self.cursor.fetchall()
        
        # task1 LINQ
        def task_1_LINQ(self):
            with self.connection:
                print("1. Найти сотрудников, опоздавших сегодня меньше чем на 5 минут")
                query = Employee.select(Employee.fio).join(EmployeeCheck).where(EmployeeCheck.type == 1).where(EmployeeCheck.date == NOW()).where(EmployeeCheck.time > '08:00:00').where((EXTRACT (HOURS FROM EmployeeCheck.time - '08:00:00') * 60 + EXTRACT (MINUTES FROM EmployeeCheck.time - '08:00:00')) < 5)
                for q in query.dicts().execute():
                    print(q)

        # task2 LINQ
        def task_2_LINQ(self):
            pass

        # task3 LINQ
        def task_3_LINQ(self):
            pass



def main():
    # Подключаемся к БД.
    status = False
    try:
        database = SQLighter('postgres', '****', 'localhost', '5432', 'lab_1')
        if database.connection:
            status = True

        print("База данных успешно открыта")

        # Запросы на уровне БД
        for elem in database.task_1_SQL:
            print(GREEN, elem)
        for elem in database.task_2_SQL:
            print(BLUE, elem)
        for elem in database.task_3_SQL:
            print(YELLOW, elem)
        
        # Запросы на уровне Приложения
        database.task_1_LINQ



    except (Exception, Error) as error:
        print("Ошибка при работе с PostgreSQL", error)
    finally:
        if status:
            database.cursor.close()
            database.connection.close()
            print("Соединение с PostgreSQL закрыто")


if __name__ == "__main__":
    main()