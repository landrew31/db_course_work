CREATE OR REPLACE FUNCTION "Lupa_A".count_goods(IN id_goods INTEGER)
RETURNS integer AS
$BODY$
DECLARE
  id_doctype integer;
  quant integer;
  moves "Lupa_A".goods_moves%ROWTYPE;
BEGIN
 
  /* 285 Чек, 288 Накладна */
  quant := 0;
    FOR moves IN SELECT * FROM "Lupa_A".goods_moves WHERE "Id_goods" = id_goods
    LOOP
      SELECT dot."Id_doctype" INTO id_doctype FROM ("Lupa_A".doc_types dot
        JOIN "Lupa_A".documentation doc ON (doc."Id_doc" = moves."Id_doc"
          AND dot."Id_doctype" = doc."Id_doctype"));
      IF id_doctype = 285 THEN
        quant := quant - moves.quantity;
      END IF;
      IF id_doctype = 288 THEN
        quant := quant + moves.quantity;
      END IF;
    END LOOP;

    
RETURN quant;
END;
$BODY$
LANGUAGE plpgsql;
