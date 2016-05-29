CREATE OR REPLACE FUNCTION "Lupa_A".show_actions_in_good(IN got_good_name VARCHAR)
RETURNS TABLE (
  action_name VARCHAR,
  percent NUMERIC,
  day_start DATE,
  day_stop DATE
) AS
$BODY$
DECLARE
  id integer;
BEGIN
 SELECT "Id_goods" INTO id 
   FROM "Lupa_A".goods 
   WHERE good_name = got_good_name;
 RETURN QUERY SELECT
   act.action_name,
   act.percent,
   act.day_start,
   act.day_stop
 FROM
   ("Lupa_A".actions act
 JOIN "Lupa_A".action_good act_go ON (act_go.id_good = id AND
   act_go.id_action = act."Id_action"));
END;
$BODY$
LANGUAGE plpgsql;
