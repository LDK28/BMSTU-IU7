-- Из 3 ЛР #1
-- Скалярная функция
-- Возврачает skill юриста по его id

-- CREATE OR REPLACE FUNCTION get_lawyer_skill_by_id (u_id INTEGER)
-- RETURNS INTEGER AS 
-- $$
-- 	SELECT skill
-- 	FROM lawyers
--     WHERE lawyers.id = u_id;
-- $$
-- LANGUAGE SQL;

-- ЗАЩИТА: та же функция, но на вход json
CREATE OR REPLACE FUNCTION get_lawyer_skill_by_id_json(u_id jsonb)
RETURNS INTEGER AS 
$$
    SELECT skill
	FROM lawyers
    WHERE lawyers.id = u_id::INT;
$$ 
LANGUAGE sql;

SELECT * FROM get_lawyer_skill_by_id_json('5') AS skill;