CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_contractor(IN got_name VARCHAR,
  IN got_phone VARCHAR, IN got_adress VARCHAR, 
  IN got_birth VARCHAR, IN got_state_number VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  IF NOT EXISTS (SELECT * FROM "Lupa_A".contractors WHERE contr_name = got_name) THEN
  INSERT INTO "Lupa_A".contractors (contr_name, phone, adress) 
    VALUES (got_name, got_phone, got_adress);
  END IF;
  SELECT "Id_contr" into id FROM "Lupa_A".contractors
    WHERE contr_name = got_name;
  IF got_birth <> '' AND 
  NOT EXISTS (SELECT * FROM "Lupa_A".individ_contr WHERE "Id_contr" = id) THEN
    INSERT INTO "Lupa_A".individ_contr (birthday, "Id_contr")
      VALUES (to_date(got_birth, 'YYYY-MM-DD'), id);
  END IF;
  IF got_state_number <> '' AND 
  NOT EXISTS (SELECT * FROM "Lupa_A".entity_contr WHERE "Id_contr" = id)THEN
    INSERT INTO "Lupa_A".entity_contr (state_number, "Id_contr")
      VALUES (got_state_number, id);
  END IF;
RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
