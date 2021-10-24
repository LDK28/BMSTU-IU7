-- 10. Инструкция SELECT, использующая поисковое выражение CASE.

SELECT  lawyers.name,
        CASE
            WHEN lawyers.skill < 5
            THEN 'Bad lawyer'
            ELSE 'Good lawyer'
        END
FROM lawyers;