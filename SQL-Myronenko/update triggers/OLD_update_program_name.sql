CREATE OR REPLACE FUNCTION "Lupa_A".update_program_name(
  IN old_name VARCHAR, IN got_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_program" into id FROM "Lupa_A".action_programs
    WHERE program_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".action_programs WHERE program_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".action_programs SET program_name = got_name WHERE program_name = old_name;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
