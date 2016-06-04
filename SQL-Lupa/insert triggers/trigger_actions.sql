CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_action()
RETURNS trigger AS
$BODY$
BEGIN
IF NEW.day_start > NEW.day_stop OR NEW.day_stop < date_trunc('day',now()) 
  OR NEW.day_start < date_trunc('day',now()) OR NEW.action_name = '' OR NEW.percent <= 0 THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_action
BEFORE INSERT
ON "Lupa_A".actions
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_action();