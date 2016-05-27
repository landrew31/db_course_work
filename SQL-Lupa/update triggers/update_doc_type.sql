CREATE OR REPLACE FUNCTION "Lupa_A".update_doc_type(
  IN old_name VARCHAR, IN got_name VARCHAR)
RETURNS integer AS
$BODY$
DECLARE
  id integer;
BEGIN
  SELECT "Id_doctype" into id FROM "Lupa_A".doc_types WHERE doc_type_name = old_name;
  IF NOT EXISTS (SELECT * FROM "Lupa_A".doc_types WHERE doc_type_name = old_name) THEN
  RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Lupa_A".doc_types SET (doc_type_name) = (got_name) 
      WHERE doc_type_name = old_name;
  END IF;

RETURN id;
END;
$BODY$
LANGUAGE plpgsql;
