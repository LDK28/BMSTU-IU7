-- 2) Пользовательскую агрегатную функцию CLR.
-- Получить кол-во юристов заданного скилла.

CREATE OR REPLACE FUNCTION count_lawyers(skill VARCHAR)
RETURNS INT
AS $$
count = 0
res = plpy.execute("SELECT * FROM lawyers")

for elem in res:
    if elem["skill"] == skill:
        count += 1

return count
$$ 
LANGUAGE plpython3u;