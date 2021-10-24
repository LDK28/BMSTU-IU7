-- 6. Инструкция SELECT, использующая предикат сравнения с квантором.

SELECT *
FROM lawyers
WHERE lawyers.skill > ALL(
	SELECT lawyers.skill
    FROM lawyers
    WHERE lawyers.id < 174)