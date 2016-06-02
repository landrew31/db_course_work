CREATE OR REPLACE VIEW documents AS SELECT
  per.per_surname || ' ' || per.per_name,
  doc.doc_date,
  dot.doc_type_name,
  "Lupa_A".count_money_for_doc(doc."Id_doc"),
  contr.contr_name
FROM 
  ( ( ( ("Lupa_A".documentation doc 
JOIN "Lupa_A".doc_types dot 
  ON (doc."Id_doctype" = dot."Id_doctype") )
JOIN "Myronenko_O".staff sta
  ON (sta."Id_staff" = doc."Id_stuff") )
JOIN "Myronenko_O".person per
  ON (per."Id_person" = sta."Id_person") )
JOIN "Lupa_A".contractors contr
  ON (contr."Id_contr" = doc."Id_contr"));
