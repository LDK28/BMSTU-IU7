CREATE TABLE IF NOT EXISTS lawyers_json
(
    doc JSON
);

INSERT INTO lawyers_json
SELECT * FROM lawyers_import;

SELECT * FROM lawyers_json;


SELECT * FROM lawyers
WHERE skill > 5
ORDER BY name
LIMIT 5;