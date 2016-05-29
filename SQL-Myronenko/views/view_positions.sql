CREATE OR REPLACE VIEW "Myronenko_O".show_positions
AS SELECT
    positions.posit_name,
    stuffCount.count,
    positions."Id_position"
FROM
  "Myronenko_O".positions positions
  join (
    SELECT
      vacancies."Id_position", count(*)
    FROM
      "Myronenko_O".staff staff
      join "Myronenko_O".vacancies vacancies on staff."Id_vacancy" = vacancies."Id_vacancy"
    WHERE
      vacancies."Id_position" = 254
      AND vacancies.date_out is NULL
    GROUP BY vacancies."Id_position")
    AS stuffCount on positions."Id_position" = stuffCount."Id_position";


GRANT SELECT ON TABLE "Myronenko_O".show_positions TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_positions TO hr_operator;
