DROP VIEW IF EXISTS FARMLAND_VIEW;

CREATE VIEW FARMLAND_VIEW AS
SELECT
	f.farmland_id,
	f.farmland_size,
	c.crop_name AS crop_type,
	e.first_name || ' ' ||
	CASE 
		WHEN e.middle_name = 'N/A' --OR e.middle_name IS NULL
		THEN ''
		ELSE e.middle_name || ' '
	END || 
	e.last_name AS overseer_name,
	j.job_title AS overseer_job_title
FROM FARMLANDS f
JOIN CROP_TYPES c ON f.crop_type_id = c.crop_id
JOIN EMPLOYEES e ON f.overseer_id = e.emp_id
JOIN JOB_TITLES j ON e.job_title_id = j.job_id;

SELECT * FROM FARMLAND_VIEW;
