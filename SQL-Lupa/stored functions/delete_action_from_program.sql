CREATE OR REPLACE FUNCTION "Lupa_A".delete_action_from_program(IN got_program_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  action_id integer;
  program_id integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_action" FROM "Lupa_A".actions
    WHERE action_name = got_action_name) THEN
    RAISE EXCEPTION 'wrong action';
  END IF;
  IF NOT EXISTS (SELECT "Id_program" FROM "Lupa_A".programs
    WHERE program_name = got_program_name) THEN
    RAISE EXCEPTION 'wrong program';
  END IF;
  SELECT "Id_action" into action_id FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  SELECT "Id_program" into program_id FROM "Lupa_A".programs
    WHERE program_name = got_program_name;
  DELETE FROM "Lupa_A".action_program WHERE 
    (id_action = action_id AND id_program = program_id);
    
RETURN action_id;
END;
$BODY$
LANGUAGE plpgsql;
