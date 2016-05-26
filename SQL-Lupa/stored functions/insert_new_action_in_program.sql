CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_action_in_program(IN got_program_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id_action integer;
  id_program integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_action" FROM "Lupa_A".actions
    WHERE action_name = got_action_name) THEN
    RAISE EXCEPTION 'wrong action';
  END IF;
  IF NOT EXISTS (SELECT "Id_program" FROM "Lupa_A".programs
    WHERE program_name = got_program_name) THEN
    RAISE EXCEPTION 'wrong program';
  END IF;
  SELECT "Id_action" into id_action FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  SELECT "Id_program" into id_program FROM "Lupa_A".programs
    WHERE program_name = got_program_name;
  INSERT INTO "Lupa_A".action_program (id_action, id_program) 
    VALUES (id_action, id_program);
    
RETURN id_action;
END;
$BODY$
LANGUAGE plpgsql;
