CREATE OR REPLACE FUNCTION "Lupa_A".update_action(
  IN old_name VARCHAR, IN got_name VARCHAR,
  IN got_percent NUMERIC, IN got_start VARCHAR, 
  IN got_stop VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_action" into id FROM "Lupa_A".actions WHERE action_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".actions WHERE action_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".actions SET (action_name, percent, day_start, day_stop) = 
      (got_name, got_percent, to_date(got_start, 'YYYY-MM-DD'), to_date(got_stop, 'YYYY-MM-DD')) 
      WHERE action_name = old_name;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
