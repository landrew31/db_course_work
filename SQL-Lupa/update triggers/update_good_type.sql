CREATE OR REPLACE FUNCTION "Lupa_A".update_good_type(
  IN old_name VARCHAR, IN got_name VARCHAR,
  IN got_term INTEGER, IN got_item VARCHAR,
  IN got_price_per_one DOUBLE PRECISION)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_goods" into id FROM "Lupa_A".goods WHERE good_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".goods WHERE good_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".goods SET (good_name, term, item, price_per_one) = 
      (got_name, got_term, got_item, got_price_per_one) 
      WHERE good_name = old_name;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
