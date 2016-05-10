CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_card(IN got_contr_name VARCHAR,
  IN got_program_name VARCHAR, IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  got_id_contr integer;
  got_id_program integer;
  got_id_action integer;
BEGIN
  SELECT "Id_contr" INTO got_id_contr FROM "Lupa_A".contractors
    WHERE contr_name = got_contr_name;
  IF EXISTS (SELECT "Id_card" FROM "Lupa_A".cards
    WHERE id_contr = got_id_contr) THEN
    RAISE EXCEPTION 'card exists';
  END IF;
  SELECT "Id_program" into got_id_program FROM "Lupa_A".action_programs
    WHERE program_name = got_program_name;
      SELECT "Id_action" into got_id_action FROM "Lupa_A".actions
    WHERE action_name = got_action_name;

  INSERT INTO "Lupa_A".cards (id_contr, programs_on_card, single_actions)
    VALUES (got_id_contr, ARRAY[got_id_program], ARRAY[got_id_action]);
    
RETURN got_id_contr;
END;
$BODY$
LANGUAGE plpgsql;
