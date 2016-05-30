CREATE OR REPLACE VIEW "Myronenko_O".show_vacancies
AS SELECT
    positions.posit_name,
    SUM(vacancies.type),
    vacancies."Id_position"
FROM
    "Myronenko_O".vacancies vacancies
    join "Myronenko_O".positions positions
        on vacancies."Id_position" = positions."Id_position"
WHERE positions.exists = TRUE
GROUP BY
	vacancies."Id_position",
	positions.posit_name;


GRANT SELECT ON TABLE "Myronenko_O".show_vacancies TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_vacancies TO hr_operator;
