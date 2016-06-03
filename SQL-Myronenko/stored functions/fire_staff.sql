CREATE OR REPLACE FUNCTION "Myronenko_O".fire_staff
    (IN id_staff integer, IN fire_date VARCHAR)
RETURNS void AS
$BODY$
DECLARE
    date_start date;
BEGIN

    IF NOT EXISTS
        (SELECT *
            FROM "Myronenko_O".staff
            WHERE
                "Id_staff" = id_staff)
        THEN RAISE EXCEPTION 'staff does not exist';
    END IF;

    SELECT staffDoc.date_in INTO date_start from (
        SELECT date_in
        FROM "Myronenko_O".staff
        WHERE
            "Id_staff" = id_staff AND
            date_out IS NULL
    ) AS staffDoc;
    IF date_start > to_date(fire_date, 'YYYY-MM-DD')
        THEN RAISE EXCEPTION 'Error. Staff cant be fired before work start.';
    END IF;

    UPDATE "Myronenko_O".staff
        SET date_out = to_date(fire_date, 'YYYY-MM-DD')
        WHERE
            "Id_staff" = id_staff AND
            date_out IS NULL;

END;
$BODY$
LANGUAGE plpgsql VOLATILE;
