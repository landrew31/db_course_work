CREATE OR REPLACE FUNCTION "Myronenko_O".update_persInfo(
  IN persId integer,
  IN newName character varying,
  IN newSurname character varying,
  IN newBirthday character varying,
  IN newEdu character varying)
RETURNS integer AS
$BODY$
BEGIN
  IF NOT EXISTS (SELECT * FROM "Myronenko_O".person WHERE Id_person = persId)
      THEN RAISE EXCEPTION 'doesn"t exists';
  ELSE
    UPDATE "Myronenko_O".person SET
        (per_name, per_surname, birthday, education) =
        (newName, newSurname, to_date(newBirthday, 'YYYY-MM-DD'), newEdu)
        WHERE Id_person = persId;
  END IF;

RETURN persId;
END;
$BODY$
LANGUAGE plpgsql
VOLATILE COST 100;
