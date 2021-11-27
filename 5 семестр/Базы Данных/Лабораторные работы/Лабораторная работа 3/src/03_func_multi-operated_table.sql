-- #3
-- Многооператорная табличная функция
-- Возврачает данные юристов чей skill между first_skill_rest и second_skill_rest


CREATE OR REPLACE FUNCTION get_lawyers_by_skill_restrictions(first_skill_rest INT, second_skill_rest INT)
RETURNS TABLE
(
    id INT,
    name VARCHAR,
    email_address VARCHAR
)
AS 
$$
BEGIN
    -- Добавить к таблице.
    RETURN QUERY
    SELECT id, name, email_address
    FROM lawyers
    WHERE skill BETWEEN first_skill_rest AND second_skill_rest;
END;
$$
LANGUAGE  plpgsql;