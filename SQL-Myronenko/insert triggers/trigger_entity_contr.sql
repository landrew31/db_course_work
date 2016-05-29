CREATE OR REPLACE FUNCTION "Myronenko_O".check_new_pers_skill()
RETURNS trigger AS
$BODY$
BEGIN
IF NOT EXISTS (SELECT * FROM "Myronenko_O".entity_contr WHERE "Id_contr" = NEW."Id_contr")
THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER check_new_pers_skill
BEFORE INSERT
ON "Myronenko_O".personal_skills
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".check_new_pers_skill();
