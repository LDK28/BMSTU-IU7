-- 3) Определяемую пользователем табличную функцию CLR.
-- Возвращает пользователей юристов заданного скилла.

CREATE OR REPLACE FUNCTION lawyers_with_skill(skill INT)
RETURNS TABLE
(
    id INT,
    name VARCHAR,
    skill INT
)
AS 
$$
    rv = plpy.execute(f" \
    SELECT id, name, skill \
    FROM lawyers")
    res = []
    for elem in rv:
        if elem["skill"] == skill:
            res.append(elem)
    return res
$$ 
LANGUAGE plpython3u;

SELECT * FROM lawyers_with_skill(5);
