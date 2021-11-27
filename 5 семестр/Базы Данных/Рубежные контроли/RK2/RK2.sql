-- Рубежный контроль 2
-- ВАРИАНТ 4

-- Задание 1.(4 балла)
-- Создать базу данных RK2. Создать в ней структуру, соответствующую
-- указанной на ER-диаграмме. Заполнить таблицы тестовыми значениями (не
-- менее 10 в каждой таблице).

CREATE DATABASE rk2;

CREATE TABLE employee(
    id SERIAL PRIMARY KEY NOT NULL,
    FIO VARCHAR,
    birth INTEGER,
    experience INTEGER,
    phone VARCHAR,

    security_post_id INTEGER NOT NULL
);

CREATE TABLE duty(
    id SERIAL PRIMARY KEY NOT NULL,
    duty_date DATE,
    working_time INTEGER
);

CREATE TABLE security_post(
    id SERIAL PRIMARY KEY NOT NULL,
    security_name VARCHAR,
    security_address VARCHAR
);

CREATE TABLE d_e(
    id SERIAL PRIMARY KEY NOT NULL,
    employee_id INTEGER NOT NULL,
    duty_id INTEGER NOT NULL
);

ALTER TABLE employee
    ADD CONSTRAINT FK_employee_to_security_post
    FOREIGN KEY (security_post_id)
    REFERENCES security_post(id);

ALTER TABLE d_e
    ADD CONSTRAINT FK_sp_e_to_employee
    FOREIGN KEY (employee_id)
    REFERENCES employee(id);

ALTER TABLE d_e
    ADD CONSTRAINT FK_sp_e_to_duty
    FOREIGN KEY (duty_id)
    REFERENCES duty(id);


-- Заполнение постов охраны
INSERT INTO security_post(security_name, security_address) 
VALUES ('ПОСТ №1', 'Москва 1'), 
        ('ПОСТ №2', 'Москва 2'),
        ('ПОСТ №3', 'Москва 3'),
        ('ПОСТ №4', 'Москва 4'),
        ('ПОСТ №5', 'Москва 5'),
        ('ПОСТ №6', 'Москва 6'),
        ('ПОСТ №7', 'Москва 7'),
        ('ПОСТ №8', 'Москва 8'),
        ('ПОСТ №9', 'Москва 9'),
        ('ПОСТ №10', 'Москва 10'),
        ('ПОСТ №11', 'Москва 11');


-- Заполнение сотрудников
INSERT INTO employee(FIO, birth, experience, phone, security_post_id) 
VALUES ('Петров П.П.', 1970, 15, '+77777777771', 10), 
        ('Васильев П.П.', 1970, 23, '+77777777772', 9),
        ('Боттас П.П.', 1980, 15, '+77777777773', 8),
        ('Тото В.П.', 1978, 20, '+77777777774', 7),
        ('Иванов П.П.', 1988, 10, '+77777777775', 6),
        ('Сидоров П.П.', 1987, 11, '+77777777776', 5),
        ('Крендельков П.П.', 1971, 20, '+77777777777', 4),
        ('Зюков П.П.', 1991, 21, '+77777777778', 3),
        ('Антонов П.П.', 1975, 21, '+77777777779', 2),
        ('Зыкин П.П.', 1995, 3, '+77777777710ы', 1);

-- Заполнение дежурств
INSERT INTO duty(duty_date, working_time) 
VALUES ('10-10-2021', 6),
        ('11-10-2021', 7),
        ('12-10-2021', 1),
        ('13-10-2021', 12),
        ('14-10-2021', 10),
        ('15-10-2021', 9),
        ('16-10-2021', 8),
        ('17-10-2021', 6),
        ('18-10-2021', 5),
        ('19-10-2021', 10);

INSERT INTO d_e(employee_id, duty_id) VALUES (1, 2);
INSERT INTO d_e(employee_id, duty_id) VALUES (1, 1);
INSERT INTO d_e(employee_id, duty_id) VALUES (2, 2);
INSERT INTO d_e(employee_id, duty_id) VALUES (1, 2);
INSERT INTO d_e(employee_id, duty_id) VALUES (5, 9);
INSERT INTO d_e(employee_id, duty_id) VALUES (6, 3);
INSERT INTO d_e(employee_id, duty_id) VALUES (2, 2);
INSERT INTO d_e(employee_id, duty_id) VALUES (8, 8);
INSERT INTO d_e(employee_id, duty_id) VALUES (10, 7);
INSERT INTO d_e(employee_id, duty_id) VALUES (7, 6);

-- Задание 2.(6 баллов)
-- Написать к разработанной базе данных 3 запроса, в комментарии указать, что
--этот запрос делает:

-- 1) 
-- Этот запрос выведет все поля таблицы и тыкже добавит еще одно поле CASE, 
-- в котором будет значение 'Great employee', если поле employee.experience > 10,
-- и 'Medium employee' иначе.
SELECT *,
        CASE
            WHEN employee.experience > 10
            THEN 'Great employee'
            ELSE 'Medium employee'
        END
FROM employee;

-- 2) Инструкция UPDATE со скалярным подзапросом в предложении SET.
-- Скалярный подзапрос возвращает стаж сотрудника с id = 4 и увеличивает его на 1, 
-- после чего присваивает(SET) жто значение сотруднику с id = 5
UPDATE employee
SET experience = 1 + (
	SELECT experience
	FROM employee
	WHERE id = 4
)
WHERE id = 5

-- 3) Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и предложения HAVING.
-- Запрос группирует сотрудников по одинаковым ФИО, после высчитывает их средний стаж и выводит только тех у кого он больше 10.
SELECT AVG(experience)
FROM employee
GROUP BY experience
HAVING AVG(experience) > 10;


-- Задание 3.(10 баллов)
-- Создать хранимую процедуру с выходным параметром, которая уничтожает
-- все SQL DDL триггеры (триггеры типа 'TR') в текущей базе данных.
-- Выходной параметр возвращает количество уничтоженных триггеров.
-- Созданную хранимую процедуру протестировать.

CREATE OR REPLACE PROCEDURE remove_ddl_triggers (count_del INOUT INT)
AS
$$
    DECLARE temp_name VARCHAR(256);
    DECLARE temp_type VARCHAR(256);
    DECLARE temp_table VARCHAR(256);
    DECLARE rec RECORD; 

BEGIN
    count_del = 0;
    for rec IN (SELECT * 
                FROM information_schema.triggers
                WHERE trigger_schema = 'public')
    LOOP
        temp_name = rec.trigger_name;
        temp_type = rec.event_manipulation;
        temp_table = rec.event_object_table;

        IF temp_type = 'CREATE' OR temp_type = 'DROP' OR temp_type = 'ALTER' 
            THEN
            EXECUTE 'drop triggers' || 'on' || temp_table;
            count_del = count_del + 1;
        END IF;
    END LOOP;

END;
$$
LANGUAGE plpgsql;

-- Проверка работы процедуры
CALL remove_ddl_triggers(0)