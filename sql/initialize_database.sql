-- Enum tables
CREATE TABLE IF NOT EXISTS ESTABLISHMENTS (
    est_id SERIAL PRIMARY KEY,
    est_name TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS CATEGORIES (
    category_id SERIAL PRIMARY KEY,
    category_name TEXT UNIQUE NOT NULL
);

-- Entities
CREATE TABLE IF NOT EXISTS TRANSACTIONS (
    trans_id SERIAL PRIMARY KEY,
    trans_est_id INTEGER NOT NULL REFERENCES ESTABLISHMENTS(est_id),
    trans_category_id INTEGER NOT NULL REFERENCES CATEGORIES(category_id),
    trans_amount NUMERIC(14,2) NOT NULL,
    trans_date DATE NOT NULL,
    trans_description TEXT
   
);

INSERT INTO ESTABLISHMENTS (est_name) VALUES ('Cafe') ON CONFLICT DO NOTHING;

INSERT INTO CATEGORIES (category_name) VALUES ('Food') ON CONFLICT DO NOTHING;

INSERT
INTO TRANSACTIONS (trans_est_id, trans_category_id, trans_amount, trans_date, trans_description)
VALUES (1, 1, -12.50, TO_DATE('18.09.2025', 'DD.MM.YYYY'), 'Lunch at cafe')
ON CONFLICT DO NOTHING;

