CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_staff()
RETURNS trigger AS
$BODY$
BEGIN

IF
    NEW.date_out IS NOT NULL AND
    OLD.date_in > NEW.date_out
THEN RAISE EXCEPTION 'invalid data. staff date-in cant be newer than date-out';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_staff
BEFORE UPDATE
ON "Myronenko_O".staff
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_staff();
