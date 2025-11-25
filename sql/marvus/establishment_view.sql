DROP VIEW IF EXISTS ESTABLISHMENT_VIEW;

CREATE VIEW ESTABLISHMENT_VIEW AS
SELECT
	e.establishment_id,
	e.establishment_name AS "Establishment name"
FROM ESTABLISHMENTS e
ORDER BY e.establishment_name;
