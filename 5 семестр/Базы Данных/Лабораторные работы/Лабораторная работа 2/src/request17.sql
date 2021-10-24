-- 17. Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса.

INSERT INTO customers (name, email_address, phone_number, court_case_id)
SELECT name, email_address, phone_number, court_case_id
FROM customers
WHERE name LIKE '%Хэм%';