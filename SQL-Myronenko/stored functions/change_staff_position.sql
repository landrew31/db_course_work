CREATE OR REPLACE FUNCTION "Myronenko_O".change_staff_position
    (IN id_person integer, IN id_new_position integer)
RETURNS void AS
$BODY$
BEGIN
    IF NOT EXISTS
        (SELECT *
            FROM "Myronenko_O".staff
            WHERE
                "Id_person" = id_person)
        THEN RAISE EXCEPTION 'person does not exist';
    END IF;

    IF NOT EXISTS
        (SELECT *
            FROM "Myronenko_O".positions
            WHERE
                "Id_position" = id_new_position)
        THEN RAISE EXCEPTION 'position does not exist';
    END IF;

    UPDATE "Myronenko_O".staff
        SET date_out = current_date
        WHERE
            "Id_person" = id_person AND
            date_out IS NULL;

    EXECUTE "Myronenko_O".add_person_on_position(
        id_person,
        id_new_position,
        to_char(current_date+1, 'YYYY-MM-DD'));
END;
$BODY$
LANGUAGE plpgsql VOLATILE;
