import psycopg2
from psycopg2 import Error
import random

names = ["Иван Бытько",
         "Иван Иванов",
         "Пьер Семёнов",
         "Алёна Прошкина",
         "Алексей Швед",
         "Тимофей Мозгов",
         "Льюис Хэммилтон",
         "Аркадий Петров",
         "Александр Петров"]

phone_numbers = ["+7(777)777-77-77",
                 "+7(777)777-11-77",
                 "+7(777)111-77-77",
                 "+7(777)454-55-77",
                 "+7(914)366-77-77",
                 "+7(777)777-56-37",
                 "+7(777)777-45-55",
                 "+1(777)797-77-77"]

email_address = ["user_mail_1@mail.com",
                 "user_mail_2@mail.com",
                 "user_mail_3@mail.com",
                 "user_mail_4@mail.com",
                 "user_mail_5@mail.com",
                 "user_mail_6@mail.com",
                 "user_mail_7@mail.com",
                 "user_mail_8@mail.com",
                 "user_mail_9@mail.com"]

address = ["Yuzhno-Sakhalinsk",
           "Tayohara",
           "Moscow",
           "Saint-Petersburg",
           "New-York",
           "Los-Angeles",
           "Vladivostok",
           "Birmingham",
           "Stambul"]

article_text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur sed imperdiet dolor. Vivamus augue " \
               "est, pretium eu felis vitae, aliquam pharetra libero. Proin sodales leo nec neque feugiat tristique. " \
               "In eget arcu tellus. Pellentesque euismod, sem non egestas suscipit, odio erat bibendum lorem, nec " \
               "eleifend mi tellus in dolor. Suspendisse."

try:
    connection = psycopg2.connect(user="postgres",
                                  password="281001",  # Your PostgreSQL passward
                                  host="localhost",  # Your DB host
                                  port="5432",  # Your PostgreSQL port
                                  database="lab_1")

    count_lawyers = int(input("lawyers: "))
    count_customers = int(input("customers: "))
    count_judgements = int(input("judgements: "))

    cursor = connection.cursor()
    if count_lawyers:
        insert_query = ""
        for i in range(count_lawyers):
            insert_query += "('{name}', '{email_address}', '{phone_number}', {skill}, '{office_address}'),".format(
                name=random.choice(names),
                email_address=random.choice(email_address),
                phone_number=random.choice(phone_numbers),
                skill=random.randint(1, 10),
                office_address=random.choice(address))

        cursor.execute(
            "INSERT INTO lawyers (name, email_address, phone_number, skill, office_address) VALUES " + insert_query[:-1])
        connection.commit()

    if count_customers:
        insert_query_cases = ""
        insert_query_customers = ""
        for i in range(count_customers):
            insert_query_cases += "('{article}', '{description}'),".format(
                article=random.randint(1, 300),
                description=article_text,
            )
            insert_query_customers += "('{name}', '{email_address}', '{phone_number}', '{court_case_id}'),".format(
                name=random.choice(names),
                email_address=random.choice(email_address),
                phone_number=random.choice(phone_numbers),
                court_case_id=i + 1
            )

        cursor.execute(
            "INSERT INTO court_cases (article, description) VALUES " + insert_query_cases[
                                                                                    :-1])
        connection.commit()
        cursor.execute(
            "INSERT INTO customers (name, email_address, phone_number, court_case_id) VALUES " + insert_query_customers[
                                                                            :-1])
        connection.commit()

    if count_judgements:
        cursor.execute(
            "SELECT id from customers")
        customers_id = cursor.fetchall()
        cursor.execute(
            "SELECT id from lawyers")
        lawyers_id = cursor.fetchall()
        insert_query = ""
        for i in range(count_judgements):
            insert_query += "('{lawyer_id}', '{customer_id}', '{judge_date}'),".format(
                lawyer_id=random.choice(lawyers_id)[0],
                customer_id=random.choice(customers_id)[0],
                judge_date="28.10.2021")
        cursor.execute(
            "INSERT INTO judgement (lawyer_id, customer_id, judge_date) VALUES " + insert_query[:-1])
        connection.commit()


except (Exception, Error) as error:
    print("Ошибка при работе с PostgreSQL", error)
finally:
    if connection:
        cursor.close()
        connection.close()
        print("Соединение с PostgreSQL закрыто")
