CREATE OR REPLACE VIEW show_cards AS 
  SELECT 
    foo1.contr_name,
    foo1.progs,
    foo2.acts
  FROM (
    SELECT
      con.contr_name,
      string_agg(pro.program_name, ', ') as progs
    FROM 
      contractors con,
      action_programs pro,
      cards
    WHERE pro."Id_program" = ANY (programs_on_card) AND
      cards.id_contr = con."Id_contr"
    GROUP BY
      con.contr_name) AS 
    foo1
  JOIN (
    SELECT
      con.contr_name,
      string_agg(act.action_name, ', ') as acts
    FROM 
      contractors con,
      actions act,
      cards
    WHERE act."Id_action" = ANY (single_actions) AND
      cards.id_contr = con."Id_contr"
    GROUP BY
      con.contr_name) AS 
    foo2
  ON 
    foo1.contr_name = foo2.contr_name
  GROUP BY
    foo1.contr_name,
    foo1.progs,
    foo2.acts;
