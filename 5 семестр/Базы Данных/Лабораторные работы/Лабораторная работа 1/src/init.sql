CREATE TABLE lawyers(
    id SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(50),
    email_address VARCHAR(50),
    phone_number VARCHAR(50),
    rating INTEGER,
    office_address VARCHAR(50)
);

CREATE TABLE customers(
    id SERIAL PRIMARY KEY NOT NULL,
    name VARCHAR(50),
    email_address VARCHAR(50),
    phone_number VARCHAR(50),
    court_case_id INTEGER NOT NULL,
    FOREIGN KEY (court_case_id) REFERENCES court_cases(id)
);

CREATE TABLE court_cases(
    id SERIAL PRIMARY KEY NOT NULL,
    article VARCHAR(50),
    description VARCHAR(1024)
);

CREATE TABLE judgement(
    id SERIAL PRIMARY KEY NOT NULL,
    lawyer_id INTEGER NOT NULL,
    customer_id INTEGER NOT NULL,
    judge_date DATE,
    FOREIGN KEY (lawyer_id) REFERENCES lawyers(id),
    FOREIGN KEY (customer_id) REFERENCES customers(id)
);


-- Доп. задание
CREATE TABLE cases(
    id SERIAL PRIMARY KEY NOT NULL,
    court_case_id INTEGER NOT NULL,
    judgement_id  INTEGER NOT NULL,
    judge_result BOOLEAN,
    FOREIGN KEY (court_case_id) REFERENCES court_case(id),
    FOREIGN KEY (judgement_id) REFERENCES judgements(id)
);