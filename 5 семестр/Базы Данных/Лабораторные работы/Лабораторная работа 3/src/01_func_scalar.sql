-- #1
-- Скалярная функция
-- Возврачает skill юриста по его id

CREATE OR REPLACE FUNCTION get_lawyer_skill_by_id (u_id INTEGER)
RETURNS INTEGER AS 
$$
	SELECT skill
	FROM lawyers
    WHERE lawyers.id = u_id;
$$
LANGUAGE SQL;