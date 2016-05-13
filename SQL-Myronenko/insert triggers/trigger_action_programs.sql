CREATE OR REPLACE FUNCTION "Lupa_A".new_program_trigger()
RETURNS trigger AS
$BODY$
BEGIN
IF NOT EXISTS (SELECT * FROM "Lupa_A".actions WHERE "Id_action" = NEW.actions_on_program[1])
  OR NEW.program_name <> '' THEN
RAISE EXCEPTION 'invalid data';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER new_program_trigger
BEFORE INSERT
ON "Lupa_A".action_programs
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".new_program_trigger();