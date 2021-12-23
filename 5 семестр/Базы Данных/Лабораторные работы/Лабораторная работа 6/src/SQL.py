import psycopg2

class SQLighter:
        def __init__(self, user, password, host, port, database):
            """Подключаемся к БД и сохраняем курсор соединения"""
            self.connection = psycopg2.connect(user=user,
                                                password=password,  # Your PostgreSQL passward
                                                host=host,  # Your DB host
                                                port=port,  # Your PostgreSQL port
                                                database=database)
            self.cursor = self.connection.cursor()

        # task1
        # scalar func
        def get_avg_skill(self):
            with self.connection:
                self.cursor.execute("SELECT AVG(skill) FROM lawyers")
                return self.cursor.fetchall()

        # task2
        # join
        def get_lawyers_judge_dates(self):
            with self.connection:
                self.cursor.execute("SELECT * "
                                    "FROM lawyers "
                                    "JOIN judgement "
                                    "ON lawyers.id = judgement.lawyer_id "
                                    "ORDER BY lawyers.id")
                return self.cursor.fetchall()

        # task3
        # partition function
        def get_lawyers_judge_count(self):
            with self.connection:
                self.cursor.execute("SELECT id, name, next_process_count FROM (\
			                        SELECT lawyers.id, lawyers.name, COUNT(lawyers.id) OVER(PARTITION BY lawyers.id) AS next_process_count, ROW_NUMBER() OVER (PARTITION BY lawyers.id ORDER BY lawyers.id) as cnt \
			                        FROM lawyers "
                                    "JOIN judgement "
                                    "ON lawyers.id = judgement.lawyer_id)\
                                    AS foo WHERE cnt = 1")
                return self.cursor.fetchall()

        # task4
        # metadata
        def get_lawyers_meta(self):
            with self.connection:
                self.cursor.execute("SELECT *\
                                    FROM information_schema.columns\
                                    WHERE\
                                    table_name = 'lawyers'")
                return self.cursor.fetchall()

        # task5
        # scalar func from lab_3
        def get_lawyers_skill_l3(self, id):
            with self.connection:
                self.cursor.execute("SELECT *\
                                    FROM get_lawyer_skill_by_id({id})".format(id = id))
                return self.cursor.fetchall()

        # task6
        # table func from lab_3
        def get_lawyers_l3(self, id):
            with self.connection:
                self.cursor.execute("SELECT *\
                                    FROM get_lawyers({id})".format(id=id))
                return self.cursor.fetchall()
        # task7
        # saved procedure from lab_3
        def insert_lawyers_l3(self):
            with self.connection:
                self.cursor.execute("CALL insert_lawyer ('Valteri', 'valera@mail.com', '+79443893838', 9, 'Boston', 1000)")

        # task8
        # system func
        def get_system_info(self):
            with self.connection:
                self.cursor.execute("SELECT current_database(), current_user;")
                return self.cursor.fetchall()

        # task9
        # create table
        def get_system_info(self):
            with self.connection:
                self.cursor.execute("CREATE TABLE lawyers_count_process("
                                    "id SERIAL PRIMARY KEY NOT NULL,"
                                    "name VARCHAR(50),"
                                    "judge_count INTEGER);")

        # task10
        # insert
        def insert_lawyer(self):
            with self.connection:
                self.cursor.execute("INSERT INTO lawyers "
                                    "(name, email_address, phone_number, skill, office_address, process_count) \
                                    VALUES ('Valteri', 'valera@mail.com', '+79443893838', 9, 'Boston', 1000)")
