CREATE OR REPLACE FUNCTION "Lupa_A".delete_action_from_card(IN got_name VARCHAR,
  IN got_action_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  got_id_action integer;
  got_id_contr integer;
BEGIN
  SELECT "Id_action" into got_id_action FROM "Lupa_A".actions
    WHERE action_name = got_action_name;
  SELECT "Id_contr" into got_id_contr FROM "Lupa_A".contractors
    WHERE contr_name = got_name;
  UPDATE "Lupa_A".cards SET single_actions = 
    ( SELECT
      array_remove( (SELECT
        single_actions FROM "Lupa_A".cards
          WHERE id_contr = got_id_contr),
        got_id_action ) )
     WHERE id_contr = got_id_contr;
    
RETURN got_id_contr;
END;
$BODY$
LANGUAGE plpgsql;
