-- 8. Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов.

SELECT  lawyers.name,
        (
            SELECT AVG(lawyers.skill)
            FROM lawyers
            WHERE lawyers.skill > 5
        ) AS AvgSkill
FROM lawyers
WHERE lawyers.name LIKE '%м%';