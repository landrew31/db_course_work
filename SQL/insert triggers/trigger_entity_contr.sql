CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_entity_contr()
RETURNS trigger AS
$BODY$
BEGIN
IF EXISTS (SELECT * FROM "Lupa_A".entity_contr WHERE "Id_contr" = NEW."Id_contr")
THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_entity_contr
BEFORE INSERT
ON "Lupa_A".entity_contr
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_entity_contr();