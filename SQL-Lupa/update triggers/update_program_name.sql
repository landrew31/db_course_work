CREATE OR REPLACE FUNCTION "Lupa_A".update_program(
  IN old_name VARCHAR, IN got_name VARCHAR,
  IN got_start VARCHAR, IN got_stop VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_program" into id FROM "Lupa_A".programs WHERE program_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".programs WHERE program_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".programs SET (program_name, day_start, day_stop) = 
      (got_name, to_date(got_start, 'YYYY-MM-DD'), to_date(got_stop, 'YYYY-MM-DD')) 
      WHERE program_name = old_name;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
