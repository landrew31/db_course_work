CREATE OR REPLACE VIEW "Myronenko_O".show_positions
AS SELECT
    positions.posit_name,
    stuffCount.count,
    positions."Id_position"
FROM
  "Myronenko_O".positions positions
  LEFT JOIN (
    SELECT
      vacancies."Id_position", count(*)
    FROM
      "Myronenko_O".staff staff
      join "Myronenko_O".vacancies vacancies
        on staff."Id_vacancy" = vacancies."Id_vacancy"
    WHERE
      staff.date_in < current_date AND
      (staff.date_out > CURRENT_DATE OR staff.date_out IS NULL)
    GROUP BY vacancies."Id_position")
    AS stuffCount on positions."Id_position" = stuffCount."Id_position"
    WHERE positions.exists = TRUE;


GRANT SELECT ON TABLE "Myronenko_O".show_positions TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_positions TO hr_operator;
