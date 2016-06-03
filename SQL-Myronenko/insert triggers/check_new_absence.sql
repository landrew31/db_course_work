CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_absence()
RETURNS trigger AS
$BODY$
BEGIN

IF NEW.date_in > NEW.date_out
THEN
RAISE EXCEPTION 'invalid data. wrong dates';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER check_new_absence
BEFORE INSERT
ON "Myronenko_O".absences
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_absence();
