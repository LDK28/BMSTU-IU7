-- #4
-- Рекурсивнуя функция или функция с рекурсивным ОТВ
-- Возврачает таблицу чисел Фиббоначи
-- P.s. Это не к моей таблице, но я просто не нашёл применения рекурсии к своей базе ;(


CREATE OR REPLACE FUNCTION fib(first INT, second INT,max INT)
RETURNS TABLE (fibonacci INT)
AS 
$$
BEGIN
    RETURN QUERY
    SELECT first;
    IF second <= max THEN
        RETURN QUERY
        SELECT *
        FROM fib(second, first + second, max);
    END IF;
END
$$
LANGUAGE plpgsql;
