-- 14. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING.

SELECT skill, AVG(process_count) AS  avg_process
FROM lawyers
GROUP BY skill;
