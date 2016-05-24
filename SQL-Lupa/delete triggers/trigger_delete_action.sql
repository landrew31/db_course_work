
CREATE OR REPLACE FUNCTION "Lupa_A".delete_action()
RETURNS trigger AS
$BODY$
DECLARE
  id integer;
BEGIN
SELECT "Id_action" into id FROM "Lupa_A".actions
    WHERE action_name = OLD.action_name;

RETURN OLD;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_action
BEFORE DELETE
ON "Lupa_A".actions
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".delete_action();