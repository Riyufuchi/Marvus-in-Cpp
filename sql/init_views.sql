DROP VIEW IF EXISTS CATEGORY_VIEW;

CREATE VIEW CATEGORY_VIEW AS
SELECT
	c.category_id,
	c.category_name AS "Category name"
FROM CATEGORIES c
ORDER BY c.category_name;

-- ESTABLISHMENTS

DROP VIEW IF EXISTS ESTABLISHMENT_VIEW;

CREATE VIEW ESTABLISHMENT_VIEW AS
SELECT
	e.establishment_id,
	e.establishment_name AS "Establishment name"
FROM ESTABLISHMENTS e
ORDER BY e.establishment_name;


-- PAYMENTS

DROP VIEW IF EXISTS PAYMENT_VIEW;

CREATE VIEW PAYMENT_VIEW AS
SELECT
	p.payment_id,
	e.establishment_name AS 'Entity',
	c.category_name AS 'Category',
	p.payment_value AS 'Value',
	strftime('%d.%m.%Y', p.payment_date) AS 'Date',
	p.payment_note AS 'Note'
FROM PAYMENTS p
JOIN ESTABLISHMENTS e ON p.establishment_id_key = e.establishment_id
JOIN CATEGORIES c ON p.category_id_key = c.category_id
ORDER BY p.payment_date;
