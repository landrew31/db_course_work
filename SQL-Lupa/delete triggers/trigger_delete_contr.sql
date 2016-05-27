CREATE OR REPLACE FUNCTION "Lupa_A".delete_contr()
RETURNS trigger AS
$BODY$
DECLARE
  id integer;
BEGIN
SELECT "Id_contr" into id FROM "Lupa_A".contractors
    WHERE contr_name = OLD.contr_name;
IF EXISTS (SELECT * FROM "Lupa_A".individ_contr WHERE "Id_contr" = OLD."Id_contr") THEN
  DELETE FROM "Lupa_A".individ_contr WHERE "Id_contr" = id;
END IF;
IF EXISTS (SELECT * FROM "Lupa_A".entity_contr WHERE "Id_contr" = OLD."Id_contr") THEN
  DELETE FROM "Lupa_A".entity_contr WHERE "Id_contr" = id;
END IF;
RETURN OLD;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_contr
BEFORE DELETE
ON "Lupa_A".contractors
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".delete_contr();