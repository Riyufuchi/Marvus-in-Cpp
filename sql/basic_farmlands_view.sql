DROP VIEW IF EXISTS FARMLAND_VIEW;

CREATE VIEW FARMLAND_VIEW AS
SELECT
	f.farmland_id,
	f.farmland_name AS "Name",
	f.farmland_size AS "Field size",
	c.crop_name AS "Crop type",
	e.first_name || ' ' ||
	CASE 
		WHEN e.middle_name = 'N/A' --OR e.middle_name IS NULL
		THEN ''
		ELSE e.middle_name || ' '
	END || 
	e.last_name AS "Overseer",
	j.job_title AS "Oversee role"
FROM FARMLANDS f
JOIN CROP_TYPES c ON f.crop_type_id = c.crop_id
JOIN EMPLOYEES e ON f.overseer_id = e.emp_id
JOIN JOB_TITLES j ON e.job_title_id = j.job_id;
