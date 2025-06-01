-- PLAYERS
INSERT INTO PLAYERS (player_name) VALUES ('Exactylus');
INSERT INTO PLAYERS (player_name) VALUES ('Dorgan Oathkeeper');
INSERT INTO PLAYERS (player_name) VALUES ('?');

-- VILLAGES
INSERT INTO VILLAGES (village_name, owner_id) VALUES ('Westfold', 1);
INSERT INTO VILLAGES (village_name, owner_id) VALUES ('Dorgan Oathkeeper village', 2);
INSERT INTO VILLAGES (village_name, owner_id) VALUES ('?', 3);

-- UNITS
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Spearman');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Swordman');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Axeman');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Archer');

INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Scout');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Light cavalry');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Mounted archer');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Heavy cavalry');

INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Ram');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Catapult');

INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Paladin');
INSERT INTO UNIT_TYPES (unit_type_name) VALUES ('Noble');

-- CAMPAIGNS
INSERT INTO CAMPAIGNS (campaign_name) VALUES ('Broken oath');

-- UNITS DETAILS

INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (50, 30, 10, 1, 1);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (30, 30, 70, 1, 2);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (60, 30, 40, 1, 3);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (100, 30, 60, 1, 4);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (50, 50, 20, 2, 5);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (125, 100, 250, 4, 6);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (250, 100, 150, 5, 7);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (200, 150, 600, 6, 8);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (300, 200, 200, 5, 9);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (320, 400, 100, 8, 10);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (20, 20, 40, 10, 11);
INSERT INTO UNITS (wood_cost, clay_cost, iron_cost, personel_cost, unit_type_name_id) VALUES (400, 500, 500, 100, 12);




