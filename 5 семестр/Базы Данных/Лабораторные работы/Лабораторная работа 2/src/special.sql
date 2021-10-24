-- Дополнительное задание на дополнительные баллы
-- Создать таблицы:
-- • Table1{id: integer, var1: string, valid_from_dttm: date, valid_to_dttm: date}
-- • Table2{id: integer, var2: string, valid_from_dttm: date, valid_to_dttm: date}
-- Версионность в таблицах непрерывная, разрывов нет (если valid_to_dttm =
-- '2018-09-05', то для следующей строки соответствующего ID valid_from_dttm =
-- '2018-09-06', т.е. на день больше). Для каждого ID дата начала версионности и
-- дата конца версионности в Table1 и Table2 совпадают.

-- Выполнить версионное соединение двух талиц по полю id.

CREATE TABLE Table1 (
    id INTEGER, 
    var1 VARCHAR(10), 
    valid_from_dttm  DATE, 
    valid_to_dttm DATE
);

CREATE TABLE Table2 (
    id INTEGER, 
    var2 VARCHAR(10), 
    valid_from_dttm  DATE, 
    valid_to_dttm DATE
);

SELECT Table1.id, 
	   Table1.var1, 
	   Table2.var2, 
	   GREATEST(Table1.valid_from_dttm, Table2.valid_from_dttm) AS valid_from_dttm, 
	   LEAST(Table1.valid_to_dttm, Table2.valid_to_dttm) AS valid_to_dttm
FROM Table1
JOIN Table2
ON Table1.valid_from_dttm < Table2.valid_to_dttm
AND Table1.valid_to_dttm > Table2.valid_from_dttm