-- 11. Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT.

SELECT skill, SUM(process_count) AS SQ
INTO Rlawyers
FROM lawyers
WHERE process_count IS NOT NULL
GROUP BY skill;