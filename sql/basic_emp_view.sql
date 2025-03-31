DROP VIEW IF EXISTS EMPLOYEE_VIEW;

CREATE VIEW EMPLOYEE_VIEW AS
SELECT e.emp_id, e.first_name, e.middle_name, e.last_name, j.job_title AS job_title
FROM EMPLOYEES e
JOIN JOB_TITLES j ON e.job_title_id = j.job_id;

SELECT * FROM EMPLOYEE_VIEW;
