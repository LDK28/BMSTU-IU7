-- 19. Инструкция UPDATE со скалярным подзапросом в предложении SET.

UPDATE lawyers
SET skill = 1 + (
	SELECT skill
	FROM lawyers
	WHERE id = 180
)
WHERE id = 180