-- Variant 4
-- РК3 ИУ7-51Б Костев Дмитрий Игоревич

CREATE TABLE IF NOT EXISTS employee(
    id INT PRIMARY KEY,
    fio VARCHAR(32),
    date_of_birth DATE,
    department VARCHAR(32)
);

CREATE TABLE IF NOT EXISTS employee_check_time(
    id INT PRIMARY KEY,
    employee_id INT,
    FOREIGN KEY (employee_id) REFERENCES employee(id),
    date DATE DEFAULT CURRENT_DATE,
    day_of_week VARCHAR,
    time TIME DEFAULT CURRENT_TIME,
    type INT CHECK (type >= 1 AND type <= 2) -- 1 - приешл, 2 - вышел
);


-- ЗАДАНИЕ 1(8 баллов)
-- Написать табличную функцию, возвращающую сотрудников, не пришедших сегодня на работу.
-- «Сегодня» необходимо вводить в качестве параметра
CREATE OR REPLACE FUNCTION check_miss(dt DATE) RETURNS TABLE
(
    fio varchar,
    department varchar
)
AS
$$
    SELECT fio, department
    FROM employee empl
    WHERE empl.id NOT IN (SELECT e.id
    FROM employee e JOIN employee_check_time ect ON e.id = ect.employee_id
    WHERE date = dt)
$$LANGUAGE SQL;

SELECT * FROM check_miss('2020-11-15');


-- ЗАДАНИЕ 2(12 баллов - по 2 балла за запрос)
--1 Первый запрос (SQL)
--Найти сотрудников, опоздавших сегодня меньше чем на 5 минут
SELECT DISTINCT fio
FROM employee e 
JOIN employee_check_time ect on e.id = ect.employee_id
WHERE type = 1 AND date = NOW() AND time > '08:00:00' 
AND 
(EXTRACT (HOURS FROM time - '08:00:00') * 60 + EXTRACT (MINUTES FROM time - '08:00:00')) < 5;


--2 Второй запрос (SQL)
--Найти сотрудников, которые выходили больше чем на 10 минут
--


--3 Третий запрос (SQL)
--Найти сотрудников бухгалтерии, приходящих на работу раньше 8:00
SELECT DISTINCT fio
FROM employee e 
JOIN employee_check_time ect on e.id = ect.employee_id
WHERE department = 'Бугхалтерия' AND type = 1 AND time < '08:00:00';
