-- Задание 1

--Создать базу данных RK2. Создать в ней структуру, соответствующую
--указанной на ER-диаграмме. Заполнить таблицы тестовыми значениями (не
--менее 10 в каждой таблице).

--CREATE DATABASE rk2;

CREATE TABLE region(
    id INT NOT NULL generated ALWAYS AS IDENTITY,
    description varchar NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE sanatorium(
    id INT NOT NULL generated ALWAYS AS IDENTITY,
    name varchar NOT NULL,
    build_year int NOT NULL,
    description varchar NOT NULL,
    region_id int NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE tourist(
    id INT NOT NULL generated ALWAYS AS IDENTITY,
    FIO varchar NOT NULL,
    born_year int NOT NULL,
    adress varchar NOT NULL, 
    mail varchar NOT NULL,
    PRIMARY KEY (id)
);
CREATE TABLE s_t(
    id INT NOT NULL generated ALWAYS AS IDENTITY,
    tourist_id INT NOT NULL,
    sanatorium_id INT NOT NULL,
    PRIMARY KEY (id)
);

ALTER TABLE sanatorium
    ADD CONSTRAINT FK_S_TO_R
    FOREIGN KEY (region_id)
    REFERENCES region(id);

ALTER TABLE s_t
    ADD CONSTRAINT FK_ST_TO_S
    FOREIGN KEY (sanatorium_id)
    REFERENCES sanatorium(id);
ALTER TABLE s_t
    ADD CONSTRAINT FK_ST_TO_T
    FOREIGN KEY (tourist_id)
    REFERENCES tourist(id);


INSERT INTO region(description) VALUES ('Море'); 
INSERT INTO region(description) VALUES ('Горы');
INSERT INTO region(description) VALUES ('Лес');
INSERT INTO region(description) VALUES ('Море');
INSERT INTO region(description) VALUES ('Лес');
INSERT INTO region(description) VALUES ('Горы');
INSERT INTO region(description) VALUES ('Лес');
INSERT INTO region(description) VALUES ('Горы'); -- 8
INSERT INTO region(description) VALUES ('Лес');
INSERT INTO region(description) VALUES ('Море');
INSERT INTO region(description) VALUES ('Лес');
-- OR
INSERT INTO region(description) VALUES ('Море'), 
                                       ('Горы'),
                                       ('Лес'),
                                       ('Море'),
                                       ('Лес'),
                                       ('Горы'),
                                       ('Лес'),
                                       ('Горы'), -- 8
                                       ('Лес'),
                                       ('Море'),
                                       ('Лес');


INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Аар', 2000, 'Море', 1);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Сар', 1999, 'Горы', 2);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Лар', 2002, 'Море', 5);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Кар', 2020, 'Горы', 4);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Пар', 2003, 'Лес', 3);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Вар', 2002, 'Море', 2);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Чар', 1993, 'Горы', 3);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Фар', 2015, 'Горы', 2);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Мар', 2016, 'Море', 7);
INSERT INTO sanatorium(name, build_year,description, region_id) VALUES ('Лар', 2001, 'Горы', 9);

INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Сартин', 2000, 'У11', 'ama');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Мартин', 1999, 'У12', 'bma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Тартин', 2003, 'У13', 'sma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Гартин', 2012, 'У15', 'dma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Партин', 2020, 'У15', 'as');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Вартин', 2013, 'У16', 'ya');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Фартин', 1993, 'У17', 'tma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Рартин', 1998, 'У18', 'xma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Картин', 2006, 'У19', 'zma');
INSERT INTO tourist(FIO, born_year, adress, mail) VALUES ('Сартин', 1999, 'У10', 'fma');

INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (1, 2);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (1, 1);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (2, 2);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (1, 2);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (5, 9);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (6, 3);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (2, 2);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (8, 8);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (10, 7);
INSERT INTO s_t(tourist_id, sanatorium_id) VALUES (7, 6);

DROP TABLE s_t;
DROP TABLE sanatorium;
DROP TABLE tourist;
DROP TABLE region;

-- Задание 2

--Написать к разработанной базе данных 3 запроса, в комментарии указать, что
--этот запрос делает:
--1) Инструкция SELECT, использующая поисковое выражение CASE
--2) Инструкция UPDATE со скалярным подзапросом в предложении SET
--3) Инструкцию SELECT, консолидирующую данные с помощью
--предложения GROUP BY и предложения HAVING

--1)Инструкция SELECT, использующая поисковое выражение CASE
-- Выводит id регионов 
-- Выводит описание у тех регионов, у которых оно ГОРЫ
SELECT id,
    CASE WHEN description LIKE 'Горы' THEN description
    END
    FROM region;
--2) Инструкция UPDATE со скалярным подзапросом в предложении SET
-- Меняет у 3 региона описание на Горы 
---(после этого запроса запрос № 1 показывает 3 региона с горами)
SELECT description FROM region WHERE id = 8;
UPDATE region SET description = (SELECT description FROM region WHERE id = 8)
WHERE id = 3;

--3) Инструкцию SELECT, консолидирующую данные с помощью
--предложения GROUP BY и предложения HAVING

-- Группирует по описанию санатории (допустим что описания могут совпадать)
-- Вычисляет средний год основания санатория с таким описанием (приемы рекламы каких лет??)
-- Выводит описание и средний год
SELECT description, avg(build_year)
FROM sanatorium
GROUP BY descriptions
HAVING avg(build_year)>2000;

-- Задание 3

--Создать хранимую процедуру с выходным параметром, которая уничтожает
--все представления в текущей базе данных. Выходной параметр возвращает
--количество уничтоженных представлений. Созданную хранимую процедуру
--протестировать.

CREATE OR REPLACE PROCEDURE public.deleter()
AS 
$$
DECLARE 
    elem information_schema.sql_identifier;
    counter int;
BEGIN
    counter = 0;
    FOR elem IN
       SELECT table_name
       FROM information_schema.VIEWS
    LOOP
        --DROP VIEW IF EXISTS elem CASCADE;
              EXECUTE 'DROP VIEW IF EXISTS '||format(elem)|| '  CASCADE';
              counter = counter + 1;
        --RAISE NOTICE 'elem = %', elem;
    END LOOP;
    RAISE NOTICE 'count = %', counter;
END;
$$ LANGUAGE 'plpgsql' 

DROP VIEW IF EXISTS vista;
CREATE VIEW vista AS SELECT 'Hello World';
CALL deleter();
SELECT *
FROM vista;



