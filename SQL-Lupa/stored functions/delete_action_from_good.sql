CREATE OR REPLACE FUNCTION "Lupa_A".delete_action_from_good(IN got_good_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  action_id integer;
  good_id integer;
BEGIN
  IF NOT EXISTS (SELECT "Id_action" FROM "Lupa_A".actions
    WHERE action_name = got_action_name) THEN
    RAISE EXCEPTION 'wrong action';
  END IF;
  IF NOT EXISTS (SELECT "Id_goods" FROM "Lupa_A".goods
    WHERE good_name = got_good_name) THEN
    RAISE EXCEPTION 'wrong good';
  END IF;
  SELECT "Id_action" into action_id FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  SELECT "Id_goods" into good_id FROM "Lupa_A".goods
    WHERE good_name = got_good_name;
  DELETE FROM "Lupa_A".action_good WHERE 
    (id_action = action_id AND id_good = good_id);
    
RETURN action_id;
END;
$BODY$
LANGUAGE plpgsql;
