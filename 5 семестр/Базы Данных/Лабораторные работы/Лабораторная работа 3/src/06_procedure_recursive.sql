-- #6
-- Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ.

-- Фибоначи. Входные параметры:
-- 1. Куда запишем результат.
-- 2. max - число, до которого будут считаться числа фибоначи.
-- Т.е. вернет наибольшее число фибоначи меньшее или равное max.
-- 3. и 4. - необязательные параметры.
-- Можно отправить два числа последовательности
-- С этих чисел и начнется счет последовательности.
CREATE OR REPLACE PROCEDURE fib_proc
(
    res INOUT INT,
    max INT,
    first INT DEFAULT 1,
    second INT DEFAULT  1
)
AS 
$$
DECLARE
    tmp INT;
BEGIN
    tmp = first + second;
    IF tmp <= max THEN
        res = tmp;
        CALL fib_proc(res, max, second, tmp);
    END IF;
END;
$$
LANGUAGE  plpgsql;