CREATE OR REPLACE FUNCTION "Lupa_A".buy_goods(IN got_contr_name VARCHAR,
  IN got_staff_name VARCHAR, IN got_doc_type VARCHAR,
  IN good_names VARCHAR[], 
  IN quantities VARCHAR[])
RETURNS integer AS
$BODY$
DECLARE
  id_contr integer;
  id_staff integer;
  id_doctype integer;
  id_doc integer;
  len integer;
  date_time timestamp with time zone;
BEGIN
  SELECT "Id_contr" into id_contr FROM "Lupa_A".contractors
    WHERE contr_name = got_contr_name;
  SELECT "Id_doctype" into id_doctype FROM "Lupa_A".doc_types
    WHERE doc_type_name = got_doc_type;
  SELECT sta."Id_staff" INTO id_staff FROM ( "Myronenko_O".staff sta
    JOIN "Myronenko_O".person per 
    ON ( sta."Id_person" = per."Id_person" 
      AND per.per_surname || ' ' || per.per_name = got_staff_name ));
  IF id_contr < 2 OR id_doctype < 2 OR id_staff < 2 THEN
    RAISE EXCEPTION 'wrog documentation data';
  END IF;
  SELECT CURRENT_TIMESTAMP AT TIME ZONE 'EEST' INTO date_time;
  INSERT INTO "Lupa_A".documentation (doc_date,"Id_doctype","Id_contr","Id_stuff")
    VALUES (date_time,id_doctype,id_contr,id_staff) RETURNING "Id_doc" into id_doc;
  SELECT array_length(good_names, 1) into len;
  
  FOR i IN 1 .. len
  LOOP
    INSERT INTO "Lupa_A".goods_moves ("Id_goods","Id_doc",quantity) 
      VALUES (cast(good_names[i] AS integer),id_doc,cast(quantities[i] AS double precision));
  END LOOP;
    
RETURN id_doc;
END;
$BODY$
LANGUAGE plpgsql;
