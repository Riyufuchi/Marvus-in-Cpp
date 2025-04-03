DROP VIEW IF EXISTS MINE_VIEW;

CREATE VIEW MINE_VIEW AS
SELECT
	m.mine_id,
	m.mine_name,
	o.ore_name AS ore_type,
	CASE
		WHEN m.is_active = 1
		THEN 'Yes'
		ELSE 'No'
	END AS is_active_status -- Alias comes AFTER CASE
FROM MINES m
JOIN ORE_TYPES o ON m.ore_type_id = o.ore_id;

SELECT * FROM MINE_VIEW;
