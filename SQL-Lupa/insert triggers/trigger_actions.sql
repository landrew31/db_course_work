CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_program()
RETURNS trigger AS
$BODY$
BEGIN
IF NEW.day_start > NEW.day_stop OR NEW.day_stop < now() OR NEW.day_start < now() THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_program
BEFORE INSERT
ON "Lupa_A".programs
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_program();