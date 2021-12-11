-- 5) Триггер CLR.
-- Создаем представление, т.к. таблицы не могут иметь INSTEAD OF triggers.

CREATE VIEW customers_new AS
SELECT * 
FROM customers
WHERE id < 15;

SELECT * FROM customers_new;

-- Заменяем удаление на мягкое удаление.
CREATE OR REPLACE FUNCTION del_customers_func()
RETURNS TRIGGER
AS $$
old_id = TD["old"]["id"]
rv = plpy.execute(f" \
UPDATE customers_new SET name = \'none\'  \
WHERE customers_new.id = {old_id}")

return TD["new"]
$$ LANGUAGE plpython3u;

CREATE TRIGGER del_customers_trigger
-- INSTEAD OF - Сработает вместо указанной операции.
INSTEAD OF DELETE ON customers_new
-- Триггер с пометкой FOR EACH ROW вызывается один раз для каждой строки,
-- изменяемой в процессе операции.
FOR EACH ROW
EXECUTE PROCEDURE del_customers_func();

DELETE FROM customers_new
WHERE name = 'ivan';