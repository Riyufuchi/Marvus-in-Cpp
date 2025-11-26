DROP VIEW IF EXISTS PAYMENT_VIEW;

CREATE VIEW PAYMENT_VIEW AS
SELECT
	p.payment_id,
	e.establishment_name AS 'Entity',
	c.category_name AS 'Category',
	p.payment_value AS 'Value',
	p.payment_date AS 'Date',
	p.payment_note AS 'Note'
FROM PAYMENTS p
JOIN ESTABLISHMENTS e ON p.establishment_id_key = e.establishment_id
JOIN CATEGORIES c ON p.category_id_key = c.category_id
ORDER BY p.payment_date;
