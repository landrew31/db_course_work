CREATE OR REPLACE FUNCTION "Lupa_A".insert_new_doc_type()
RETURNS trigger AS
$BODY$
BEGIN
IF EXISTS (SELECT * FROM "Lupa_A".doc_types WHERE doc_type_name = NEW.doc_type_name)
THEN
RAISE EXCEPTION 'already exists';
END IF;
RETURN NEW;
END;
$BODY$
LANGUAGE plpgsql;

CREATE TRIGGER insert_new_doc_type
BEFORE INSERT
ON "Lupa_A".doc_types
FOR EACH ROW
EXECUTE PROCEDURE "Lupa_A".insert_new_doc_type();