-- 13. Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3.

SELECT id, name, phone_number
FROM lawyers
WHERE skill = (
    SELECT MAX(skill)
    FROM lawyers
    WHERE skill < (
        SELECT AVG(skill)
        FROM lawyers
        WHERE process_count > (
            SELECT AVG(process_count)
            FROM lawyers
        )
    )
)