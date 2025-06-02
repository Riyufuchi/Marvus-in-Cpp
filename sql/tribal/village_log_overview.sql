DROP VIEW IF EXISTS VILLAGES_WITH_OWNERS;

CREATE VIEW VILLAGES_WITH_OWNERS AS
SELECT
	v.village_id,
	v.village_name AS 'Village',
	p.player_name AS 'Owner'
FROM VILLAGES v
JOIN PLAYERS p ON v.owner_id = p.player_id;
