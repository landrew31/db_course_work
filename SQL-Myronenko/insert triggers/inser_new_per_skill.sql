CREATE OR REPLACE FUNCTION "Myronenko_O".insert_new_per_skill()
RETURNS trigger AS
$BODY$
BEGIN

IF EXISTS(
    SELECT "Id_per_skils"
        FROM "Myronenko_O".personal_skills
        WHERE
            "Id_person" = NEW."Id_person" AND
            "Id_skill" = NEW."Id_skill";
        )
THEN RAISE EXCEPTION 'invalid data. pers skill already exists';
END IF;

RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_per_skill
BEFORE INSERT
ON "Myronenko_O".personal_skills
FOR EACH ROW
EXECUTE PROCEDURE "Myronenko_O".insert_new_per_skill();
