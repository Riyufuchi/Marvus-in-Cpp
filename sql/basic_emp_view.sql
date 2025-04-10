DROP VIEW IF EXISTS EMPLOYEE_VIEW;

CREATE VIEW EMPLOYEE_VIEW AS
SELECT
	e.emp_id,
	e.first_name AS "Name",
	e.middle_name AS "Middle name",
	e.last_name AS "Last name",
	j.job_title AS "Job title"
FROM EMPLOYEES e
JOIN JOB_TITLES j ON e.job_title_id = j.job_id;
