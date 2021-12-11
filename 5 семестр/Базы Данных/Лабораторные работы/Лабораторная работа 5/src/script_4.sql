-- 4. Выполнить следующие действия:
-- 4.1. Извлечь XML/JSON фрагмент из XML/JSON документа
CREATE TABLE IF NOT EXISTS court_cases_id_article
(
    id INT,
    article VARCHAR
);

SELECT * FROM court_cases_import, json_populate_record(null::court_cases_id_article, doc);

-- Получаем id и имена всех юзеров
-- У кроторых nickname начинается с буквы 'A'
SELECT id, article
FROM court_cases_import, json_populate_record(null::court_cases_id_article, doc)
WHERE article LIKE '1%';

-- Оператор -> возвращает поле объекта JSON как JSON.
-- -> - выдаёт поле объекта JSON по ключу.
SELECT * FROM court_cases_import;

SELECT doc->'id' AS id, doc->'article' AS article
FROM court_cases_import;



-- 4.2. Извлечь значения конкретных узлов или атрибутов XML/JSON документа
CREATE TABLE descr(doc jsonb);
-- Оружие: огнестрельное: пистолет, ручное: нож
INSERT INTO descr VALUES ('{"id":0, "description": {"stat":"123", "hand_weapon":"knife"}}');
INSERT INTO descr VALUES ('{"id":1, "description": {"stat":"644", "hand_weapon":"minigun"}}');

SELECT * FROM descr;

-- Извлекаем огнестрельное оружие у пользователей.
SELECT doc->'id' AS id, doc->'description'->'stat' AS stat
FROM descr;

-- 4.3. Выполнить проверку существования узла или атрибута
-- Проверка вхождения — важная особенность типа jsonb, не имеющая аналога для типа json.
-- Эта проверка определяет, входит ли один документ jsonb в другой.
-- (https://postgrespro.ru/docs/postgresql/9.5/datatype-json#json-containment)

-- В данном примере проверятся существование описания у пользователя с id=u_id.
CREATE OR REPLACE FUNCTION if_descr(u_id jsonb)
RETURNS VARCHAR AS '
    SELECT CASE
               WHEN count.cnt > 0
                   THEN ''true''
               ELSE ''false''
               END AS comment
    FROM (
             SELECT COUNT(doc -> ''id'') cnt
             FROM descr
             WHERE doc -> ''id'' @> u_id
         ) AS count;
' LANGUAGE sql;

SELECT * FROM descr;

SELECT if_descr('1');

-- 4.4. Изменить XML/JSON документ

INSERT INTO descr VALUES ('{"id":3, "description": {"stat":"123", "hand_weapon":"none"}}');


SELECT * FROM descr;
-- Особенность конкатенации json заключается в перезаписывании.
SELECT doc || '{"id": 33}'::jsonb
FROM descr;

-- Перезаписываем значение json поля.
UPDATE descr
SET doc = doc || '{"id": 33}'::jsonb
WHERE (doc->'id')::INT = 3;

SELECT * FROM descr;

-- 4.5. Разделить XML/JSON документ на несколько строк по узлам
-- Игра, которую юзер прошел.
CREATE TABLE IF NOT EXISTS passed_process(doc JSON);

INSERT INTO passed_process VALUES ('[{"user_id": 0, "process_id": 1},
  {"user_id": 2, "process_id": 2}, {"user_id": 3, "process_id": 1}]');

SELECT * FROM passed_process;

-- jsonb_array_elements - Разворачивает массив JSON в набор значений JSON.
SELECT jsonb_array_elements(doc::jsonb)
FROM passed_process;