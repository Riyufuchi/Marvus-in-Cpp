CREATE VIEW IF NOT EXISTS DAILY_TOTAL AS
SELECT 
	date(payment_date) AS day,  -- extract only the date part
	SUM(CAST(payment_value AS REAL)) AS daily_total
FROM PAYMENTS
GROUP BY date(payment_date)
ORDER BY date(payment_date);