CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_skill()
RETURNS trigger AS
$BODY$
BEGIN
IF char_length(NEW.skill_name) = 0
THEN
RAISE EXCEPTION 'invalid data';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER check_new_skill
BEFORE INSERT
ON "Myronenko_O".skills
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_skill();
