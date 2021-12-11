-- Задание из 3 ЛР
-- #5
-- Хранимая процедура без параметров или с параметрами
-- Добавляет юриста

-- CREATE OR REPLACE PROCEDURE insert_lawyer (id INT, 
--                                            name VARCHAR, 
--                                            email_address VARCHAR, 
--                                            phone_number VARCHAR, 
--                                            skill INT, 
--                                            office_address VARCHAR, 
--                                            process_count INT)
-- AS 
-- $$
-- BEGIN
--     INSERT INTO lawyers 
--     VALUES (id, name, email_address, phone_number, skill, office_address, process_count);
-- END;
-- $$
-- LANGUAGE plpgsql;

-- Задача: переделать под CLR
CREATE OR REPLACE PROCEDURE add_lawyer (   name VARCHAR, 
                                           email_address VARCHAR, 
                                           phone_number VARCHAR, 
                                           skill INT, 
                                           office_address VARCHAR, 
                                           process_count INT)
AS 
$$

plan = plpy.prepare("INSERT INTO lawyers VALUES($1, $2, $3, $4, $5, $6)", ["VARCHAR", "VARCHAR", "VARCHAR", "INT", "VARCHAR", "INT"])
rv = plpy.execute(plan, [name, email_address, phone_number, skill, office_address, process_count])
$$
LANGUAGE plpython3u;