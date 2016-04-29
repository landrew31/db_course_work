CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_individ_contr()
RETURNS trigger AS
$BODY$
BEGIN
IF EXTRACT(YEAR from AGE(NEW.birthday)) < 18 OR 
EXISTS (SELECT * FROM "Lupa_A".individ_contr WHERE "Id_contr" = NEW."Id_contr")
THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_individ_contr
BEFORE INSERT
ON "Lupa_A".individ_contr
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_individ_contr();