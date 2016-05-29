CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_action_in_good(IN got_good_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id_action integer;
  id_good integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_action" FROM "Lupa_A".actions
    WHERE action_name = got_action_name) THEN
    RAISE EXCEPTION 'wrong action';
  END IF;
  IF NOT EXISTS (SELECT "Id_goods" FROM "Lupa_A".goods
    WHERE good_name = got_good_name) THEN
    RAISE EXCEPTION 'wrong good';
  END IF;
  SELECT "Id_action" into id_action FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  SELECT "Id_goods" into id_good FROM "Lupa_A".goods
    WHERE good_name = got_good_name;
  INSERT INTO "Lupa_A".action_good (id_action, id_good) 
    VALUES (id_action, id_good);
    
RETURN id_action;
END;
$BODY$
LANGUAGE plpgsql;
