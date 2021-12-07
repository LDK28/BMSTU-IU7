-- #7
-- Хранимая процедура с курсором.

-- создание лоальной временной переменной
SELECT *
INTO tmp_lawyers
FROM lawyers
WHERE skill > 11;

CREATE OR REPLACE PROCEDURE insert_min_skills()
AS
$BODY$
DECLARE
    --объявляем курсор
    my_cursor CURSOR FOR SELECT name, email_address, phone_number, skill, office_address, process_count
                         FROM lawyers
                         WHERE skill = 5;
    tmp tmp_lawyers;

BEGIN
    OPEN my_cursor;--открываем курсор
    LOOP --начинаем цикл по курсору
		FETCH my_cursor
		INTO tmp;

		--если такого периода и не возникнет, то мы выходим
		EXIT WHEN NOT FOUND;

        INSERT INTO tmp_lawyers (name, email_address, phone_number, skill, office_address, process_count) 
        SELECT name, email_address, phone_number, skill, office_address, process_count 
        FROM tmp WHERE tmp.id = MIN(tmp.id);

    END LOOP;--заканчиваем цикл по курсору

    CLOSE my_cursor; --закрываем курсор
END;
$BODY$
LANGUAGE plpgsql;

call insert_min_skills();