-- 15. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и предложения HAVING.

SELECT skill, AVG(process_count) AS  avg_process
FROM lawyers
GROUP BY skill
HAVING AVG(process_count) > 30;