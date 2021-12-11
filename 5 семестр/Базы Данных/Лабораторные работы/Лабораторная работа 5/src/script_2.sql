-- 2. Выполнить загрузку и сохранение JSON файла в таблицу.
-- Созданная таблица после всех манипуляций должна соответствовать таблице
-- базы данных, созданной в первой лабораторной работе.

-- Создаем новую таблицу, чтобы сравнить ее со старой.
-- Да и вообще, чтобы не дропать старую таблицу...

CREATE TABLE IF NOT EXISTS court_cases_copy(
    id SERIAL PRIMARY KEY NOT NULL,
    article VARCHAR(50),
    description VARCHAR(1024)
);

-- Копируем данные из таблицы court_cases в файл court_cases.json
-- (В начале нужно поставить \COPY).
COPY(
    SELECT row_to_json(c_c) result FROM court_cases c_c
)
TO '\Users\1\Desktop\BMSTU-IU7\5 семестр\Базы Данных\Лабораторные работы\Лабораторная работа 5\src\court_cases.json';
-- Замечание: путь не должен содержать русских символов и пробелов, postgres их не понимает)

-- Подготовка данных завершена.
-- Собственно далее само задание.

-- Помещаем файл в таблицу БД.
-- Создаем таблицу, которая будет содержать json кортежи.
CREATE TABLE IF NOT EXISTS court_cases_import(doc json);

-- Теперь копируем данные в созданную таблицу.
-- (Но опять же делаем это с помощью \COPY).
COPY court_cases_import FROM '\Users\1\Desktop\BMSTU-IU7\5 семестр\Базы Данных\Лабораторные работы\Лабораторная работа 5\src\court_cases.json';

SELECT * FROM court_cases_import;

-- В принципе можно было сделать так, но т.к. в условии написано
-- Выгрузить из файла, так что нужно использовтаь copy.

-- CREATE TABLE IF NOT EXISTS court_cases_tmp(doc json);
-- INSERT INTO court_cases_tmp
-- SELECT row_to_json(c_c) result FROM court_cases c_c;
-- SELECT * FROM court_cases_tmp;

-- Данный запрос преобразует данные из строки в формате json
-- В табличное предстваление. Т.е. разворачивает объект из json в табличную строку.
SELECT * FROM court_cases_import, json_populate_record(null::court_cases_copy, doc);
-- Преобразование одного типа в другой null::users_copy
SELECT * FROM court_cases_import, json_populate_record(CAST(null AS court_cases_copy ), doc);

-- Загружаем в таблицу сконвертированные данные из формата json из таблицы users_import.
INSERT INTO court_cases_copy
SELECT id, article, description
FROM court_cases_import, json_populate_record(null::court_cases_copy, doc);

SELECT * FROM court_cases_copy;