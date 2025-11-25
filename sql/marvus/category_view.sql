DROP VIEW IF EXISTS CATEGORY_VIEW;

CREATE VIEW CATEGORY_VIEW AS
SELECT
	c.category_id,
	c.category_name AS "Category name"
FROM CATEGORIES c
ORDER BY c.category_name;
