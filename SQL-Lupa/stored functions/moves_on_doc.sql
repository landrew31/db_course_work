CREATE OR REPLACE FUNCTION "Lupa_A".moves_on_doc(IN doc_id VARCHAR)
RETURNS TABLE (
  good_name VARCHAR,
  price_per_one DOUBLE PRECISION,
  item VARCHAR,
  term INTEGER,
  quantity DOUBLE PRECISION,
  total_price DOUBLE PRECISION
) AS
$BODY$
DECLARE
  id_contr integer;
BEGIN
 SELECT contr."Id_contr" INTO id_contr FROM
   ("Lupa_A".contractors contr JOIN "Lupa_A".documentation doc
   ON (doc."Id_doc" = cast(doc_id as integer) AND doc."Id_contr" = contr."Id_contr"));
 RETURN QUERY SELECT
   goo.good_name,
   goo.price_per_one,
   goo.item,
   goo.term,
   mov.quantity,
   "Lupa_A".count_money_transaction(mov."Id_move",id_contr)
 FROM
   ("Lupa_A".goods_moves mov
 JOIN "Lupa_A".goods goo ON (goo."Id_goods" = mov."Id_goods" AND
   mov."Id_doc" = cast(doc_id as integer) ));
END;
$BODY$
LANGUAGE plpgsql;
