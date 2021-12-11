-- 3. Создать таблицу, в которой будет атрибут(-ы) с типом JSON, или
-- добавить атрибут с типом JSON к уже существующей таблице.
-- Заполнить атрибут правдоподобными данными с помощью команд INSERT или UPDATE

-- Создаем таблицу, которая будет содержать
-- Нарушителей в json формате.
CREATE TABLE IF NOT EXISTS blacklist_json
(
    data json
);

SELECT * FROM blacklist_json;

-- Вставляем в нее json строку.
-- json_object - формирует объект JSON.
INSERT INTO blacklist_json
SELECT * FROM json_object('{customer_id, lawyer_id, text}', '{1, 2, "Qwerty"}');