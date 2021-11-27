ALTER TABLE lawyers
ADD CONSTRAINT process_count_check CHECK (process_count >= 0),
ADD CONSTRAINT skill_check CHECK (skill BETWEEN 0 AND 10),
ADD CONSTRAINT email_address_check CHECK (email_address LIKE '%@%');


ALTER TABLE customers
ADD CONSTRAINT email_address_check CHECK (email_address LIKE '%@%');

