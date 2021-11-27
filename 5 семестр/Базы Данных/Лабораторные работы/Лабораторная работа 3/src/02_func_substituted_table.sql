-- #2
-- Подставляемая табличная функция
-- Возврачает данные юриста по его id

CREATE OR REPLACE FUNCTION get_lawyers (u_id INTEGER)
RETURNS lawyers AS 
$$
	SELECT *
	FROM lawyers
	WHERE lawyers.id = u_id
$$
LANGUAGE SQL;