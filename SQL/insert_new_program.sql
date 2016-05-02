CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_program(IN got_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_action" FROM "Lupa_A".actions
    WHERE action_name = got_action_name) THEN
    RAISE EXCEPTION 'wrong action';
  END IF;
  IF EXISTS (SELECT "Id_program" FROM "Lupa_A".action_programs 
    WHERE program_name = got_name) THEN
    RAISE EXCEPTION 'program exists';
  END IF;
  SELECT "Id_action" into id FROM "Lupa_A".actions
    WHERE action_name = got_action_name;

  INSERT INTO "Lupa_A".action_programs (program_name, actions_on_program)
    VALUES (got_name, ARRAY[id]);
    
RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
