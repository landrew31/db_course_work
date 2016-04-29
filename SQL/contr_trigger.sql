CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_contr()
RETURNS trigger AS
$BODY$
BEGIN
IF char_length(NEW.contr_name) = 0 OR char_length(NEW.phone) = 0 OR char_length(NEW.adress) = 0 THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_contr
BEFORE INSERT
ON "Lupa_A".contractors
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_contr();