-- #10
-- Триггер INSTEAD OF.
-- INSTEAD OF - Сработает вместо указанной операции.

-- Заменяем удаление на мягкое удаление.
-- Т.е. при попытки удалить юриста, он не будет
-- Удален, а лишь поставлен process_count = 0
-- Что будет свидетельствовать о том
-- Что у данного юриста больше нет стажа.
-- VIEW - вирутальная табоица.

CREATE VIEW lawyers_new AS
SELECT * -- INTO device_new
FROM lawyers
WHERE skill < 6;

-- drop VIEW lawyers_new;

SELECT * FROM lawyers_new;

CREATE OR REPLACE FUNCTION del_lawyer_func()
RETURNS TRIGGER
AS '
BEGIN
    RAISE NOTICE ''New =  %'', new;

    UPDATE lawyers_new
    SET process_count = 0
    WHERE lawyers_new.id = old.id;

    RETURN new;
END;
' LANGUAGE plpgsql;

CREATE TRIGGER del_device_trigger
INSTEAD OF DELETE ON lawyers_new
    FOR EACH ROW
    EXECUTE PROCEDURE del_lawyer_func();

DELETE FROM lawyers_new
WHERE process_count = 54;

SELECT * FROM lawyers_new;