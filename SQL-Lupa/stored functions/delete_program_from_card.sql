CREATE OR REPLACE FUNCTION "Lupa_A".delete_program_from_card(IN got_contr_name VARCHAR,
  IN got_program_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  card_id integer;
  program_id integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_program" FROM "Lupa_A".programs
    WHERE program_name = got_program_name) THEN
    RAISE EXCEPTION 'wrong program';
  END IF;
  IF NOT EXISTS (SELECT ind."Id_ind" 
    FROM 
      ("Lupa_A".individ_contr ind 
    JOIN "Lupa_A".contractors contr ON
      (ind."Id_contr" = contr."Id_contr" AND
       contr.contr_name = got_contr_name))) THEN
     RAISE EXCEPTION 'wrong program';
  END IF;
  SELECT "Id_program" into program_id FROM "Lupa_A".programs
    WHERE program_name = got_program_name;
  SELECT ind."Id_ind" into card_id
    FROM 
      ("Lupa_A".individ_contr ind 
    JOIN "Lupa_A".contractors contr ON
      (ind."Id_contr" = contr."Id_contr" AND
       contr.contr_name = got_contr_name));
  DELETE FROM "Lupa_A".individ_contr_program WHERE 
    (id_individ = card_id AND id_program = program_id);
    
RETURN program_id;
END;
$BODY$
LANGUAGE plpgsql;
