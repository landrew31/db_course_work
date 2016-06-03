CREATE OR REPLACE FUNCTION "Lupa_A".count_money_transaction(IN id_move INTEGER, IN id_contr INTEGER)
RETURNS double precision AS
$BODY$
DECLARE
  id_doctype integer;
  percent numeric;
  id_ind integer;
  id_doc integer;
  sum double precision;
  one_sum double precision;
  moves "Lupa_A".goods_moves%ROWTYPE;
  programs "Lupa_A".programs%ROWTYPE;
  actions "Lupa_A".actions%ROWTYPE;
BEGIN
  SELECT doc."Id_doc" INTO id_doc
    FROM ("Lupa_A".documentation doc
    JOIN "Lupa_A".goods_moves mov ON (doc."Id_doc" = mov."Id_doc" AND mov."Id_move" = id_move));
  SELECT dot."Id_doctype" INTO id_doctype 
    FROM ("Lupa_A".doc_types dot 
    JOIN "Lupa_A".documentation doc ON (doc."Id_doc" = id_doc AND doc."Id_doctype" = dot."Id_doctype"));
  /* 285 Чек, 288 Накладна */
  SELECT "Id_ind" INTO id_ind FROM "Lupa_A".individ_contr WHERE "Id_contr" = id_contr;
  SELECT * INTO moves FROM "Lupa_A".goods_moves WHERE "Id_move" = id_move;
  sum := 0;
  percent := 0;
  IF id_doctype = 288 THEN
    one_sum := moves.quantity * (SELECT price_per_one 
      FROM "Lupa_A".goods WHERE "Id_goods" = moves."Id_goods");
    sum := sum + one_sum;
  END IF;

  IF id_doctype = 285 THEN
    
      one_sum := moves.quantity * (SELECT price_per_one 
        FROM "Lupa_A".goods WHERE "Id_goods" = moves."Id_goods");
      FOR programs IN (SELECT prog.* FROM
         ("Lupa_A".programs prog
         JOIN "Lupa_A".individ_contr_program ind_prog ON 
            (ind_prog.id_individ = id_ind  AND
             ind_prog.id_program = prog."Id_program")) )

      LOOP
        FOR actions IN (SELECT act.* FROM ("Lupa_A".actions act
          JOIN "Lupa_A".action_program act_pro ON 
            (act_pro.id_program = programs."Id_program" AND
             act_pro.id_action = act."Id_action")) )
      
        LOOP
          IF EXISTS (SELECT * FROM "Lupa_A".action_good 
                WHERE id_action = actions."Id_action" AND id_good = moves."Id_goods") 
                AND percent < actions.percent THEN
             percent := actions.percent;
          END IF;
        END LOOP;
      END LOOP;
      one_sum := one_sum * 1.5 * (1 - percent / 100);
      sum := sum + one_sum;

  END IF;
    
RETURN sum;
END;
$BODY$
LANGUAGE plpgsql;
