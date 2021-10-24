-- 24. Оконные функции. Использование конструкций MIN/MAX/AVG OVER().

SELECT L.id, L.skill, L.process_count, J.judge_date, J.customer_id,
    AVG(L.skill) OVER(PARTITION BY L.process_count) AS AvgSkill,
    MIN(L.skill) OVER(PARTITION BY L.process_count) AS MinSkill,
    MAX(L.skill) OVER(PARTITION BY L.process_count) AS MaxSkill
FROM lawyers AS L LEFT OUTER JOIN judgement AS J
ON J.lawyer_id = L.id
ORDER BY L.id;