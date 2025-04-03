-- People

INSERT INTO EMPLOYEES (first_name, middle_name, last_name, job_title_id) VALUES ('Pagan', 'N/A', 'Min', 1);
INSERT INTO EMPLOYEES (first_name, middle_name, last_name, job_title_id) VALUES ('John', 'N/A', 'Doe', 3);
INSERT INTO EMPLOYEES (first_name, middle_name, last_name, job_title_id) VALUES ('Paul', 'De Pleur', 'Harmon', 4);

-- Farmlands

INSERT INTO FARMLANDS (farmland_name, farmland_size, crop_type_id, overseer_id) VALUES ('Kyra Tea Farm', 10, 2, 2);
INSERT INTO FARMLANDS (farmland_name, farmland_size, crop_type_id, overseer_id) VALUES ('Kyra Tea Terraces', 40, 1, 1);
INSERT INTO FARMLANDS (farmland_name, farmland_size, crop_type_id, overseer_id) VALUES ('City of Pain', 10, 4, 3);

-- Mines

INSERT INTO MINES (mine_name, is_active, ore_type_id) VALUES ('Pradhana', 1, 2);
INSERT INTO MINES (mine_name, is_active, ore_type_id) VALUES ('Rija', 1, 3);
INSERT INTO MINES (mine_name, is_active, ore_type_id) VALUES ('Svargiya', 0, 1);
INSERT INTO MINES (mine_name, is_active, ore_type_id) VALUES ('#4', 1, 4);
