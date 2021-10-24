-- 23. Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение.

WITH SpetialLawyers(id, process_count, skill)
AS (
	SELECT l.id, l.process_count, l.skill, 0 AS Level
	FROM lawyers AS l
	WHERE id = 172
    UNION ALL
    SELECT l.id, l.process_count, l.skill, Level + 1
    FROM lawyers AS l
    INNER JOIN SpetialLawyers AS sl
    ON l.id = sl.id
)
SELECT *
FROM SpetialLawyers