CREATE OR REPLACE FUNCTION "Lupa_A".delete_program()
RETURNS trigger AS
$BODY$
BEGIN
IF NOT EXISTS (SELECT "Id_program" FROM "Lupa_A".action_programs
    WHERE program_name = OLD.program_name) THEN
      RAISE EXCEPTION 'wrong name';
END IF;
RETURN OLD;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER delete_program
BEFORE DELETE
ON "Lupa_A".action_programs
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".delete_program();