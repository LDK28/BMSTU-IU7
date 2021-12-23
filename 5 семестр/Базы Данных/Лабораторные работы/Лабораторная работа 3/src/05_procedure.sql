-- #5
-- Хранимая процедура без параметров или с параметрами
-- Добавляет юриста


CREATE OR REPLACE PROCEDURE insert_lawyer (u_name VARCHAR, 
                                           u_email_address VARCHAR, 
                                           u_phone_number VARCHAR, 
                                           u_skill INT, 
                                           u_office_address VARCHAR, 
                                           u_process_count INT)
AS 
$$
BEGIN
    INSERT INTO lawyers (name, email_address, phone_number, skill, office_address, process_count)
    VALUES (u_name, u_email_address, u_phone_number, u_skill, u_office_address, u_process_count);
END;
$$
LANGUAGE plpgsql;