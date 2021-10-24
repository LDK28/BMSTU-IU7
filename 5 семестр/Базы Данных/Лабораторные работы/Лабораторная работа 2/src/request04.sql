-- 4. Инструкция SELECT, использующая предикат IN с вложенным подзапросом.

SELECT customers.id, customers.name, customers.phone_number
FROM customers
WHERE customers.email_address IN (
    SELECT customers.email_address
    FROM customers
    WHERE customers.name LIKE '%Арк%'
);