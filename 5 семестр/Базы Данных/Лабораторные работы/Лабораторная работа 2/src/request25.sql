-- 25. Оконные фнкции для устранения дублей

SELECT *
FROM (
    SELECT L.id,  L.name, L.skill,
    ROW_NUMBER() OVER (PARTITION BY L.skill ORDER BY L.skill) as cnt_skill
    FROM lawyers AS L
) AS foo WHERE cnt_skill = 1;