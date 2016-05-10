CREATE OR REPLACE FUNCTION "Lupa_A".update_contractor(
  IN old_name VARCHAR, IN got_name VARCHAR,
  IN got_phone VARCHAR, IN got_adress VARCHAR, 
  IN got_birth VARCHAR, IN got_state_number VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_contr" into id FROM "Lupa_A".contractors
    WHERE contr_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".contractors WHERE contr_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".contractors SET (contr_name, phone, adress) = (got_name, got_phone, got_adress) WHERE contr_name = old_name;
  END IF;
  IF got_birth <> '' AND 
  NOT EXISTS (SELECT * FROM "Lupa_A".individ_contr WHERE "Id_contr" = id) THEN
    INSERT INTO "Lupa_A".individ_contr (birthday, "Id_contr")
      VALUES (to_date(got_birth, 'YYYY-MM-DD'), id);
  END IF;
  IF got_birth <> '' THEN
    UPDATE "Lupa_A".individ_contr SET birthday = to_date(got_birth, 'YYYY-MM-DD') WHERE "Id_contr" = id;
  END IF;
  IF got_birth = '' THEN
    DELETE FROM "Lupa_A".individ_contr WHERE "Id_contr" = id;
  END IF;
  IF got_state_number <> '' AND 
  NOT EXISTS (SELECT * FROM "Lupa_A".entity_contr WHERE "Id_contr" = id)THEN
    INSERT INTO "Lupa_A".entity_contr (state_number, "Id_contr")
      VALUES (got_state_number, id);
  END IF;
  IF got_state_number <> '' THEN
    UPDATE "Lupa_A".entity_contr SET state_number = got_state_number WHERE "Id_contr" = id; 
  END IF;
  IF got_state_number = '' THEN
    DELETE FROM "Lupa_A".entity_contr WHERE "Id_contr" = id;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
