CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_abs_type()
RETURNS trigger AS
$BODY$
BEGIN

IF char_length(NEW.abs_name) = 0
THEN
RAISE EXCEPTION 'invalid data. absence name length cant be 0';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER check_new_abs_type
BEFORE INSERT
ON "Myronenko_O".absence_type
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_abs_type();
