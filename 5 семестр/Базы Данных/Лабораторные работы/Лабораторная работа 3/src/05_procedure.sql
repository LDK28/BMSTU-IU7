-- #5
-- Хранимая процедура без параметров или с параметрами
-- Добавляет юриста


CREATE OR REPLACE PROCEDURE insert_lawyer (id INT, 
                                           name VARCHAR, 
                                           email_address VARCHAR, 
                                           phone_number VARCHAR, 
                                           skill INT, 
                                           office_address VARCHAR, 
                                           process_count INT)
AS 
$$
BEGIN
    INSERT INTO lawyers 
    VALUES (id, name, email_address, phone_number, skill, office_address, process_count);
END;
$$
LANGUAGE plpgsql;