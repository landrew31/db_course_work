CREATE OR REPLACE FUNCTION "Lupa_A".show_program_in_card(IN got_contr_name VARCHAR)
RETURNS TABLE (
  program_name VARCHAR,
  day_start DATE,
  day_stop DATE
) AS
$BODY$
DECLARE
  id integer;
BEGIN
 SELECT ind."Id_ind" INTO id 
   FROM ("Lupa_A".individ_contr ind JOIN
     "Lupa_A".contractors contr ON
     (ind."Id_contr" = contr."Id_contr" AND
      contr.contr_name = got_contr_name));
 RETURN QUERY SELECT
   prog.program_name,
   prog.day_start,
   prog.day_stop
 FROM
   ("Lupa_A".programs prog
 JOIN "Lupa_A".individ_contr_program ind_prog ON 
   (ind_prog.id_individ = id AND
    ind_prog.id_program = prog."Id_program"));
END;
$BODY$
LANGUAGE plpgsql;
