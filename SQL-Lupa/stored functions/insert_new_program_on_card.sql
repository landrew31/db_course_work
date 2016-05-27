CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_program_in_card(IN got_contr_name VARCHAR,
  IN got_program_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id_card integer;
  id_program integer;
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
  SELECT "Id_program" into id_program FROM "Lupa_A".programs
    WHERE program_name = got_program_name;
  SELECT ind."Id_ind" into id_card
    FROM 
      ("Lupa_A".individ_contr ind 
    JOIN "Lupa_A".contractors contr ON
      (ind."Id_contr" = contr."Id_contr" AND
       contr.contr_name = got_contr_name));
  INSERT INTO "Lupa_A".individ_contr_program (id_individ, id_program) 
    VALUES (id_card, id_program);
    
RETURN id_card;
END;
$BODY$
LANGUAGE plpgsql;
