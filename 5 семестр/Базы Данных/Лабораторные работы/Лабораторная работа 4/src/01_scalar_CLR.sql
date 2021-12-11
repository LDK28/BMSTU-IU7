-- create extension plpython3u;


-- 1) Определяемую пользователем скалярную функцию CLR.
-- Получить имя потребителя по id.
CREATE OR REPLACE FUNCTION get_customer_name(customer_id INT)
RETURNS VARCHAR
AS $$
res = plpy.execute(f" \
    SELECT name \
    FROM customers  \
    WHERE id = {customer_id};")
if res:
    return res[0]['name']
$$ 
LANGUAGE plpython3u;

SELECT * FROM get_customer_name(5) as "Customer name";
