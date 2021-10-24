-- 12. Инструкция SELECT, использующая вложенные коррелированные подзапросы в качестве производных таблиц в предложении FROM.

SELECT id, name, phone_number
FROM lawyers
WHERE skill > (
    SELECT MAX(skill)
    FROM lawyers
    WHERE name LIKE '%Хэм%'
);
ORDER BY id