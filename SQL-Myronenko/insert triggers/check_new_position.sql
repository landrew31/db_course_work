CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_staff()
RETURNS trigger AS
$BODY$
BEGIN

IF char_length(NEW.posit_name) = 0
THEN
RAISE EXCEPTION 'invalid data. position name length cant be 0';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER check_new_position
BEFORE INSERT
ON "Myronenko_O".positions
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_position();
