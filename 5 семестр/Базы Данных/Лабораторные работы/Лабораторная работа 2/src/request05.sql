-- 5. Инструкция SELECT, использующая предикат EXISTS с вложенным подзапросом.

SELECT customers.id, customers.name, customers.phone_number
FROM customers
WHERE EXISTS (
    SELECT customers.email_address
    FROM customers
    WHERE customers.name LIKE '%Арк%'
);