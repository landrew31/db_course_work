CREATE OR REPLACE FUNCTION "Lupa_A".show_action_in_program(IN got_program_name VARCHAR)
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
 SELECT "Id_program" INTO id 
   FROM "Lupa_A".programs 
   WHERE program_name = got_program_name;
 RETURN QUERY SELECT
   act.action_name,
   act.percent,
   act.day_start,
   act.day_stop
 FROM
   ("Lupa_A".actions act
 JOIN "Lupa_A".action_program act_pro ON (act_pro.id_program = id AND
   act_pro.id_action = act."Id_action"));
END;
$BODY$
LANGUAGE plpgsql;
