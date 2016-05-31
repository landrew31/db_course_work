CREATE OR REPLACE VIEW "Myronenko_O".show_shortStaffInfo AS
    SELECT staff."Id_staff", person.per_name, person.per_surname, positions.posit_name
      FROM "Myronenko_O".staff
    JOIN "Myronenko_O".person person
          ON staff."Id_person" = person."Id_person"
    JOIN "Myronenko_O".vacancies vacancies
          ON staff."Id_vacancy" = vacancies."Id_vacancy"
    JOIN "Myronenko_O".positions positions
          ON vacancies."Id_position" = positions."Id_position";

GRANT SELECT ON TABLE "Myronenko_O".show_shortStaffInfo TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_shortStaffInfo TO hr_operator;
