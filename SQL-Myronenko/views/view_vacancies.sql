CREATE OR REPLACE VIEW "Myronenko_O".show_vacancies
AS SELECT
    positions.posit_name,
    vacancies.amount,
    vacancies.date_in,
    vacancies.date_out,
    vacancies."Id_vacancy",
    positions."Id_position"
FROM
  "Myronenko_O".vacancies vacancies
  join "Myronenko_O".positions positions on vacancies."Id_position" = positions."Id_position";


GRANT SELECT ON TABLE "Myronenko_O".show_vacancies TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_vacancies TO hr_operator;
