-- 22. Инструкция SELECT, использующая простое обобщенное табличное выражение.

WITH SpetialLawyers(process_count, skill)
AS (
	SELECT process_count, AVG(skill)
	FROM lawyers
	WHERE process_count > 20
	GROUP BY process_count
)
SELECT *
FROM SpetialLawyers