CREATE OR REPLACE FUNCTION "Myronenko_O".insert_new_person()
RETURNS trigger AS
$BODY$
BEGIN

IF char_length(NEW.per_name) = 0 OR
    char_length(NEW.per_surname) = 0 OR
    char_length(NEW.education) = 0 OR
    EXTRACT(YEAR from AGE(NEW.birthday)) < 18
THEN
RAISE EXCEPTION 'invalid person data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_person
BEFORE INSERT
ON "Myronenko_O".person
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".insert_new_person();
