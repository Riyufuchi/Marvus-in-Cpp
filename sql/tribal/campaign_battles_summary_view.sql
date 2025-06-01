DROP VIEW IF EXISTS CAMPAIGN_BATTLES_SUMMARY;

CREATE VIEW CAMPAIGN_BATTLES_SUMMARY AS
SELECT
	cl.campaign_log_id,
	c.campaign_name AS "Campaign",
	CASE WHEN b.is_offense = 1 THEN 'Yes' ELSE 'No' END AS "Attack",
	-- Target village and owner
	tv.village_name || ' (' || tp.player_name || ')' AS "Target village",
	-- Source village and owner
	sv.village_name || ' (' || sp.player_name || ')' AS "Source village",
	-- Aggregated units
	IFNULL(SUM(bul.send_units), 0) AS "Units sent",
	IFNULL(SUM(bul.lost_units), 0) AS "Units lost",
	-- Survival rate
	ROUND(
	(1.0 - (CAST(SUM(bul.lost_units) AS REAL) / NULLIF(SUM(bul.send_units), 0))) * 100,
	2) || ' %' AS "Survival rate",
	
	( b.wood_loot - IFNULL(SUM(bul.lost_units * u.wood_cost), 0) ) AS "Net wood",
	( b.clay_loot - IFNULL(SUM(bul.lost_units * u.clay_cost), 0) ) AS "Net clay",
	( b.iron_loot - IFNULL(SUM(bul.lost_units * u.iron_cost), 0) ) AS "Net iron"

	
FROM CAMPAIGN_LOG cl
JOIN CAMPAIGNS c ON cl.campaign_id = c.campaign_id
JOIN BATTLES b ON cl.battle_id = b.battle_id

-- Target village and its owner
JOIN VILLAGES tv ON b.target_village_id = tv.village_id
JOIN PLAYERS tp ON tv.owner_id = tp.player_id

-- Source village and its owner
JOIN VILLAGES sv ON b.source_village_id = sv.village_id
JOIN PLAYERS sp ON sv.owner_id = sp.player_id

-- Units used in battle
LEFT JOIN BATTLE_UNIT_LOG bul ON bul.battle_id = b.battle_id
LEFT JOIN UNITS u ON u.unit_type_name_id = bul.unit_type_id

GROUP BY cl.campaign_log_id;

