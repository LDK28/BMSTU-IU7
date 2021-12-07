-- #Дполнительное задание
-- Запишите функцию, чтобы по id данных для дел выдавалась информация, был ли суд. И если был, то кто участвовал (юрист и судья).

CREATE OR REPLACE FUNCTION get_info(u_id INT)
RETURN info AS
$$
SELECT * FROM judgement
WHERE judgement.customer_id =(
	SELECT id FROM customers
	WHERE customers.court_case_id = u_id
);
$$
LANGUAGE plpgsql;