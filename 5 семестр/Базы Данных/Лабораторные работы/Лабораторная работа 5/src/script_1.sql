-- 1. Из таблиц базы данных, созданной в первой
-- лабораторной работе, извлечь данные в JSON.

-- Функция row_to_json - Возвращает кортеж в виде объекта JSON.
SELECT row_to_json(c) result FROM customers c;
SELECT row_to_json(l) result FROM lawyers l;
SELECT row_to_json(j) result FROM judgement j;
SELECT row_to_json(c_c) result FROM court_cases c_c;