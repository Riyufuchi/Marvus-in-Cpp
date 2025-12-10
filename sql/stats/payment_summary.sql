CREATE VIEW IF NOT EXISTS PAYMENT_SUMMARY AS
WITH data AS (
	SELECT CAST(payment_value AS REAL) AS payment_real_value
	FROM PAYMENTS
),
summary AS (
	SELECT
		COUNT(*) AS total_sum,
		SUM(CASE WHEN payment_real_value > 0 THEN payment_real_value END) AS income_total,
		SUM(CASE WHEN payment_real_value < 0 THEN payment_real_value END) AS expenses_total
	FROM data
)
SELECT 'Payments' AS 'Metric',
	total_sum AS 'Total',
	ROUND(total_sum / 12.0, 2) AS 'Year average',
	ROUND(total_sum / 365.0, 2) AS 'Daily average'
FROM summary
UNION ALL
SELECT 'Income',
	ROUND(income_total, 2),
	ROUND(income_total / 12.0, 2),
	ROUND(income_total / 365.0, 2)
FROM summary
UNION ALL
SELECT 'Spendings',
	ROUND(expenses_total, 2),
	ROUND(expenses_total / 12.0, 2),
	ROUND(expenses_total / 365.0, 2)
FROM summary
UNION ALL
SELECT 'Profit',
	ROUND((income_total + expenses_total), 2),
	ROUND((income_total + expenses_total) / 12.0, 2),
	ROUND((income_total + expenses_total) / 365.0, 2)
FROM summary;

