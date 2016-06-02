CREATE OR REPLACE VIEW "Myronenko_O".show_free_persons
AS SELECT
    per_name,
    per_surname,
    "Id_person"
FROM
    "Myronenko_O".person
WHERE
    "Id_person" NOT IN (
        SELECT "Id_person"
        FROM "Myronenko_O".staff
        WHERE date_out IS NULL
    );

GRANT SELECT ON TABLE "Myronenko_O".show_free_persons TO admin;
GRANT SELECT ON TABLE "Myronenko_O".show_free_persons TO hr_operator;
