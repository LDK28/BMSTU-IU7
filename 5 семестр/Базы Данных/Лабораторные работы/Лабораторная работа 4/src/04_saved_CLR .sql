-- 4) Хранимую процедуру CLR.
-- Добавляет нового пользователя.

CREATE OR REPLACE PROCEDURE add_customer
(
    name VARCHAR,
    email_address VARCHAR,
    phone_number VARCHAR,
    court_case_id INT
)
AS 
$$

-- Чтобы юзать так, нужно подругому назвать входные параметры.
-- plpy.execute(f"INSERT INTO users VALUES({id}, \'{nick name}\', \'{sex}\', {number_of_hours}, {id_device});")

-- Функция plpy.prepare подготавливает план выполнения для запроса.
-- Передается строка запроса и список типов параметров.

plan = plpy.prepare("INSERT INTO customers VALUES($1, $2, $3, $4)", ["VARCHAR", "VARCHAR", "VARCHAR", "INT"])
rv = plpy.execute(plan, [id, name, email_address, phone_number, court_case_id])
$$
LANGUAGE plpython3u;

CALL add_customer("ivan", 'Alice@2345.ru', "+79140990909", 234);