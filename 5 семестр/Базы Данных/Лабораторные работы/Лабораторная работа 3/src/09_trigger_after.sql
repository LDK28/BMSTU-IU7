-- Триггер - Объект. Ответ на событие.
-- Инфа про триггеры:
-- https://postgrespro.ru/docs/postgresql/9.6/sql-createtrigger

-- #9
-- Триггер AFTER.
-- Когда в таблице меняется id человека (на new.id),
-- То нужно поменять у всех остальных юзеров invited_id на new.id.
-- Т.е. поменять id того человека, который их пригласил

SELECT * INTO customers_tmp
FROM customers;

CREATE OR REPLACE FUNCTION update_trigger()
RETURNS TRIGGER
AS '
BEGIN
    RAISE NOTICE ''New =  %'', new;
    RAISE NOTICE ''Old =  %'', old; 
	
    UPDATE customers_tmp
    SET court_case_id = 99
    WHERE customers_tmp.court_case_id = old.court_case_id;
    --     Для операций INSERT и UPDATE возвращаемым значением должно быть NEW.
    RETURN new;
END;
' LANGUAGE plpgsql;

-- AFTER - оперделяет, что заданная функция будет вызываться после события.
CREATE TRIGGER log_update
AFTER UPDATE ON customers_tmp
-- Триггер с пометкой FOR EACH ROW вызывается один раз для каждой строки,
-- изменяемой в процессе операции.
FOR EACH ROW
EXECUTE PROCEDURE update_trigger();

UPDATE customers_tmp
SET name = 'Игнатов Игнат'
WHERE id = 1;

SELECT * FROM customers_tmp;