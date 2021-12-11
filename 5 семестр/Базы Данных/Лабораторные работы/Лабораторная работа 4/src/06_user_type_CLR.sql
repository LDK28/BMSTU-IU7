-- 6) Определяемый пользователем тип данных CLR.
-- Тип содержит скилл и кол-во процессов юристов такого скилла.

CREATE TYPE process_count AS
(
	skill INT,
	count INT
);

CREATE OR REPLACE FUNCTION get_process_count(skill INT)
RETURNS process_count
AS
$$
    plan = plpy.prepare("      \
    SELECT skill, COUNT(process) \
    FROM lawyers                \
    WHERE skill = $1           \
    GROUP BY skill;", ["INT"])

    rv = plpy.execute(plan, [clr])

    -- nrows - возвращает кол-во строк, обработанных командой.
    if (rv.nrows()):
        return (rv[0]["skill"], rv[0]["count"])
$$ 
LANGUAGE plpython3u;

SELECT * FROM get_process_count(6);