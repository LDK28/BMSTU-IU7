-- #2
-- Подставляемая табличная функция
-- Возврачает данные юриста по его id

CREATE OR REPLACE FUNCTION get_lawyers (u_id INTEGER)
RETURNS lawyers AS 
$$
	SELECT * FROM judgement
	WHERE judgement.customer_id = (
			SELECT id FROM customers
			WHERE customers.court_case_id = u_id;
		)
$$
LANGUAGE SQL;