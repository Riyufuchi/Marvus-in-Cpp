-- File: create_view_transactions.sql

CREATE OR REPLACE VIEW view_transactions AS
SELECT
    t.trans_id,
    e.est_name AS "Establishment",
    c.category_name AS "Category",
    t.trans_amount AS "Value",
    TO_CHAR(t.trans_date,'DD.MM.YYYY') AS "Data",
    t.trans_description AS "Note"
FROM
    transactions t
    JOIN establishments e ON t.trans_est_id = e.est_id
    JOIN categories c ON t.trans_category_id = c.category_id
ORDER BY
    t.trans_date DESC, t.trans_id DESC;
