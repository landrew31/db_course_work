CREATE OR REPLACE FUNCTION "Myronenko_O".insert_new_nec_skill()
RETURNS trigger AS
$BODY$
BEGIN

IF EXISTS(
    SELECT "Id_nec_skill"
        FROM "Myronenko_O".neccessary_skills
        WHERE
            "Id_skill" = NEW."Id_skill" AND
            "Id_position" = NEW."Id_position"
        )
THEN RAISE EXCEPTION 'invalid data. nec skill already exists';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_nec_skill
BEFORE INSERT
ON "Myronenko_O".neccessary_skills
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".insert_new_nec_skill();
