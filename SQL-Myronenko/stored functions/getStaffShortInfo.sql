CREATE OR REPLACE FUNCTION "Myronenko_O".getStaffShortInfo
    (IN staffId integer)
RETURNS table (id_staff integer) AS
$BODY$
BEGIN

    SELECT person.per_name, person.per_surname, positions.posit_name
        FROM "Myronenko_O".staff
        JOIN "Myronenko_O".person person
            ON staff."Id_person" = person."Id_person"
        JOIN "Myronenko_O".vacancies vacancies
            ON staff."Id_vacancy" = vacancies."Id_vacancy"
        JOIN "Myronenko_O".positions positions
            ON vacancies."Id_position" = positions."Id_position"
        WHERE "Id_staff" = $1;

END;
$BODY$
LANGUAGE plpgsql;
