DROP VIEW IF EXISTS MINE_VIEW;

CREATE VIEW MINE_VIEW AS
SELECT
	m.mine_id,
	m.mine_name AS "Name",
	o.ore_name AS "Ore type",
	CASE
		WHEN m.is_active = 1
		THEN 'Yes'
		ELSE 'No'
	END AS "Active" -- Alias comes AFTER CASE
FROM MINES m
JOIN ORE_TYPES o ON m.ore_type_id = o.ore_id;
