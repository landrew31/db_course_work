CREATE OR REPLACE VIEW "Myronenko_O".show_staff
AS SELECT
    posit_name,
    per_name,
    per_surname,
    staff.date_in,
    staff.date_out,
    staff."Id_staff",
    staff."Id_person",
    staff."Id_vacancy",
    vacancies."Id_position",
    staff."Id_absence"
FROM
  "Myronenko_O".staff staff
  join "Myronenko_O".person persons on staff."Id_person" = persons."Id_person"
  join "Myronenko_O".vacancies vacancies on staff."Id_vacancy" = vacancies."Id_vacancy"
  join "Myronenko_O".positions positions on vacancies."Id_position" = positions."Id_position";

GRANT SELECT ON TABLE "Myronenko_O".show_staff TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_staff TO hr_operator;
