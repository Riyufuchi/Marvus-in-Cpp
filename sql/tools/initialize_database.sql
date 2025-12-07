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

CREATE TABLE IF NOT EXISTS PAYMENTS (
	payment_id INTEGER PRIMARY KEY,
	establishment_id_key INTEGER NOT NULL,
	category_id_key INTEGER NOT NULL,
	payment_value TEXT NOT NULL CHECK(CAST(payment_value AS REAL) != 0),
	payment_date DATE NOT NULL,
	payment_note TEXT DEFAULT '',
	
	FOREIGN KEY (establishment_id_key) REFERENCES ESTABLISHMENTS(establishment_id),
	FOREIGN KEY (category_id_key) REFERENCES CATEGORIES(category_id)
);

CREATE TABLE IF NOT EXISTS PAYMENT_MACROS (
	macro_id INTEGER PRIMARY KEY,
	establishment_id_key INTEGER NOT NULL,
	category_id_key INTEGER NOT NULL,
	payment_value TEXT NOT NULL,
	payment_note TEXT DEFAULT '',
	
	FOREIGN KEY (establishment_id_key) REFERENCES ESTABLISHMENTS(establishment_id),
	FOREIGN KEY (category_id_key) REFERENCES CATEGORIES(category_id)
);

-- Trigers

CREATE TRIGGER IF NOT EXISTS TRIGGER_PAYMENT_DATE_INSERT_CHECK
BEFORE INSERT ON PAYMENTS
FOR EACH ROW
BEGIN
	SELECT CASE
		WHEN NEW.payment_date IS NULL
			THEN RAISE(ABORT, 'Date cannot be NULL.')
		WHEN NEW.payment_date NOT GLOB '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]'
			THEN RAISE(ABORT, 'Date format must be YYYY-MM-DD.')
		WHEN strftime('%Y-%m-%d', NEW.payment_date) != NEW.payment_date
			THEN RAISE(ABORT, 'Invalid date (nonexistent day or month).')
		ELSE NULL
	END;
END;

CREATE TRIGGER IF NOT EXISTS TRIGGER_PAYMENT_DATE_UPDATE_CHECK
BEFORE UPDATE OF date ON PAYMENTS
FOR EACH ROW
BEGIN
	SELECT CASE
		WHEN NEW.payment_date NOT GLOB '[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]'
			THEN RAISE(ABORT, 'Date format must be YYYY-MM-DD.')
		WHEN strftime('%Y-%m-%d', NEW.payment_date) != NEW.payment_date
			THEN RAISE(ABORT, 'Invalid date (nonexistent day or month).')
		ELSE NULL
	END;
END;

