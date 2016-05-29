CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_good_type()
RETURNS trigger AS
$BODY$
BEGIN
IF EXISTS (SELECT * FROM "Lupa_A".goods WHERE good_name = NEW.good_name)
THEN
RAISE EXCEPTION 'already exists';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_good_type
BEFORE INSERT
ON "Lupa_A".goods
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_good_type();