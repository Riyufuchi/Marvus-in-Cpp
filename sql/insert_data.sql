INSERT INTO ESTABLISHMENTS (est_name) VALUES ('Cafe') ON CONFLICT DO NOTHING;

INSERT INTO CATEGORIES (category_name) VALUES ('Food') ON CONFLICT DO NOTHING;

INSERT
INTO TRANSACTIONS (trans_est_id, trans_category_id, trans_amount, trans_date, trans_description)
VALUES (1, 1, -12.50, TO_DATE('18.09.2025', 'DD.MM.YYYY'), 'Lunch at cafe')
ON CONFLICT DO NOTHING;