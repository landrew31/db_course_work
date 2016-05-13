CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_action_in_program(IN got_name VARCHAR,
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
  SELECT "Id_action" into id FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  UPDATE "Lupa_A".action_programs SET actions_on_program = 
    ( SELECT
      array_append( (SELECT
        actions_on_program FROM "Lupa_A".action_programs
          WHERE program_name = got_name),
        id ) )
     WHERE program_name = got_name;
    
RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
