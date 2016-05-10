CREATE OR REPLACE VIEW show_contractors AS SELECT
  con.contr_name,
  con.phone,
  con.adress,
  ind.birthday,
  ent.state_number
FROM ((contractors con
  LEFT JOIN individ_contr ind ON ((con."Id_contr" = ind."Id_contr")))
  LEFT JOIN entity_contr ent ON ((con."Id_contr" = ent."Id_contr")))