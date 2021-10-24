-- 21. Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE.

DELETE
FROM lawyers
WHERE skill in (
    SELECT skill
    FROM lawyers
    WHERE skill < 2
);