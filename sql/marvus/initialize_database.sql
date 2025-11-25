-- Enum tables

CREATE TABLE IF NOT EXISTS ESTABLISHMENTS (
	establishment_id INTEGER PRIMARY KEY,
	establishment_name TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS CATEGORIES (
	category_id INTEGER PRIMARY KEY,
	category_name TEXT UNIQUE NOT NULL
);

-- Entities

CREATE TABLE IF NOT EXISTS PAYMENT (
	payment_id INTEGER PRIMARY KEY,
	establishment_id_key INTEGER NOT NULL,
	category_id_key INTEGER NOT NULL,
	payment_value REAL NOT NULL CHECK(payment_value != 0),
	payment_date DATE NOT NULL,
	payment_note TEXT,
	
	FOREIGN KEY (establishment_id_key) REFERENCES ESTABLISHMENTS(establishment_id),
	FOREIGN KEY (category_id_key) REFERENCES CATEGORIES(category_id)
);

-- Trigers

CREATE TRIGGER IF NOT EXISTS trg_payment_date_check
BEFORE INSERT ON PAYMENT
FOR EACH ROW
BEGIN
	SELECT CASE
		WHEN NEW.date IS NULL
			THEN RAISE(ABORT, 'Date cannot be NULL.')
		WHEN NEW.date NOT GLOB '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]'
			THEN RAISE(ABORT, 'Date format must be YYYY-MM-DD.')
		WHEN strftime('%Y-%m-%d', NEW.date) != NEW.date
			THEN RAISE(ABORT, 'Invalid date (nonexistent day or month).')
		ELSE NULL
	END;
END;

CREATE TRIGGER IF NOT EXISTS trg_payment_date_update_check
BEFORE UPDATE OF date ON PAYMENT
FOR EACH ROW
BEGIN
	SELECT CASE
		WHEN NEW.date NOT GLOB '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]'
			THEN RAISE(ABORT, 'Date format must be YYYY-MM-DD.')
		WHEN strftime('%Y-%m-%d', NEW.date) != NEW.date
			THEN RAISE(ABORT, 'Invalid date (nonexistent day or month).')
		ELSE NULL
	END;
END;

