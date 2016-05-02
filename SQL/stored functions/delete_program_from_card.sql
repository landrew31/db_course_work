CREATE OR REPLACE FUNCTION "Lupa_A".delete_program_from_card(IN got_name VARCHAR,
  IN got_program_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  got_id_program integer;
  got_id_contr integer;
BEGIN
  SELECT "Id_program" into got_id_program FROM "Lupa_A".action_programs
    WHERE program_name = got_program_name;
  SELECT "Id_contr" into got_id_contr FROM "Lupa_A".contractors
    WHERE contr_name = got_name;
  UPDATE "Lupa_A".cards SET programs_on_card = 
    ( SELECT
      array_remove( (SELECT
        programs_on_card FROM "Lupa_A".cards
          WHERE id_contr = got_id_contr),
        got_id_program ) )
     WHERE id_contr = got_id_contr;
    
RETURN got_id_contr;
END;
$BODY$
LANGUAGE plpgsql;
