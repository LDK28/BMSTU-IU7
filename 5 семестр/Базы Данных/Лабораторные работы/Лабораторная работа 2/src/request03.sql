-- 3. Инструкция SELECT, использующая предикат LIKE.

SELECT customers.name, customers.name
FROM customers
WHERE customers.email_address LIKE '%mail_7%'