CREATE OR REPLACE FUNCTION "Lupa_A".moves_on_doc(IN doc_id VARCHAR)
RETURNS TABLE (
  good_name VARCHAR,
  price_per_one NUMERIC,
  item VARCHAR,
  term INTEGER,
  quantity DOUBLE PRECISION,
  total_price DOUBLE PRECISION
) AS
$BODY$
DECLARE
  id integer;
BEGIN
 RETURN QUERY SELECT
   goo.good_name,
   goo.price_per_one,
   goo.item,
   mov.quantity,
   mov.quantity * goo.price_per_one
 FROM
   ("Lupa_A".goods_moves mov
 JOIN "Lupa_A".goods goo ON (goo."Id_goods" = mov."Id_goods" AND
   mov."Id_doc" = doc_id ));
END;
$BODY$
LANGUAGE plpgsql;
