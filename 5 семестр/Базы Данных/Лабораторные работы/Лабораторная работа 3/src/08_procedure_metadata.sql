-- #8
-- Хранимуая процедура доступа к метаданным.
-- Получаем название атрибутов и их тип.

-- Инфа про метаданные:
-- https://postgrespro.ru/docs/postgresql/9.6/infoschema-columns

CREATE OR REPLACE PROCEDURE metadata(name VARCHAR) -- Получает название таблицы.
AS '
    DECLARE
        myCursor CURSOR FOR
            SELECT column_name,
                   data_type
           -- INFORMATION_SCHEMA обеспечивает доступ к метаданным о базе данных.
           -- columns - данные о столбацых.
            FROM information_schema.columns
            WHERE table_name = name;
        -- RECORD - переменная, которая подстравивается под любой тип.
        tmp RECORD;
BEGIN
        OPEN myCursor;
        LOOP
            FETCH myCursor
            INTO tmp;
            EXIT WHEN NOT FOUND;
            RAISE NOTICE ''column name = %; data type = %'', tmp.column_name, tmp.data_type;
        END LOOP;
        CLOSE myCursor;
END;
' LANGUAGE plpgsql;

CALL metadata('lawyers');