DROP VIEW IF EXISTS CAMPAIGN_SUMMARY;

CREATE VIEW CAMPAIGN_SUMMARY AS
WITH lost_resources_per_battle AS (
	SELECT
		b.battle_id,
		SUM(bul.lost_units * u.wood_cost) AS lost_wood,
		SUM(bul.lost_units * u.clay_cost) AS lost_clay,
		SUM(bul.lost_units * u.iron_cost) AS lost_iron
	FROM BATTLES b
	JOIN BATTLE_UNIT_LOG bul ON bul.battle_id = b.battle_id
	JOIN UNITS u ON bul.unit_type_id = u.unit_type_name_id
	GROUP BY b.battle_id
), battle_loot AS (
	SELECT
		battle_id,
		wood_loot,
		clay_loot,
		iron_loot
	FROM BATTLES
)
SELECT
	c.campaign_id,
	c.campaign_name AS 'Campaign',
	SUM(COALESCE(bl.wood_loot, 0) - COALESCE(lr.lost_wood, 0)) AS 'Wood gained',
	SUM(COALESCE(bl.clay_loot, 0) - COALESCE(lr.lost_clay, 0)) AS 'Clay gained',
	SUM(COALESCE(bl.iron_loot, 0) - COALESCE(lr.lost_iron, 0)) AS 'Iron gained',
	SUM(COALESCE(bl.wood_loot, 0)) AS 'Wood looted',
	SUM(COALESCE(bl.clay_loot, 0)) AS 'Clay looted',
	SUM(COALESCE(bl.iron_loot, 0)) AS 'Iron looted',
	SUM(COALESCE(lr.lost_wood, 0)) AS 'Wood needed',
	SUM(COALESCE(lr.lost_clay, 0)) AS 'Clay needed',
	SUM(COALESCE(lr.lost_iron, 0)) AS 'Iron needed'
FROM CAMPAIGNS c
JOIN CAMPAIGN_LOG cl ON c.campaign_id = cl.campaign_id
JOIN BATTLES b ON b.battle_id = cl.battle_id
LEFT JOIN lost_resources_per_battle lr ON lr.battle_id = b.battle_id
LEFT JOIN battle_loot bl ON bl.battle_id = b.battle_id
GROUP BY c.campaign_id;
