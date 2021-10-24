-- 9. Инструкция SELECT, использующая простое выражение CASE.

SELECT  lawyers.id, lawyers.name,
        CASE skill
            WHEN 10 THEN 'The best lawyer'
            WHEN 5 THEN 'Junior lawyer'
            ELSE 'Undefined status'
        END
FROM lawyers;