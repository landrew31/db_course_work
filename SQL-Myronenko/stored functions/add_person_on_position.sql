CREATE OR REPLACE FUNCTION "Myronenko_O".add_person_on_position
    (IN id_person integer, IN id_position integer, IN startDate VARCHAR)
RETURNS void AS
$BODY$
DECLARE
    opened_vac_by_position integer;
    position_exists boolean;
    new_vac_id integer;
BEGIN
    IF NOT EXISTS
        (SELECT *
            FROM "Myronenko_O".positions
            WHERE
                "Id_position" = id_position AND
                exists = TRUE)
        THEN RAISE EXCEPTION 'position does not exist';
    END IF;

    SELECT sum(type) INTO opened_vac_by_position
        FROM "Myronenko_O".vacancies
        WHERE "Id_position" = id_position
        GROUP BY "Id_position";
    IF opened_vac_by_position <= 0
        THEN RAISE EXCEPTION 'no vacancies on this position';
    END IF;

    SELECT nextval('inc_primary'::regclass) INTO new_vac_id;
    INSERT INTO "Myronenko_O".vacancies ("Id_vacancy", type, date, "Id_position")
        VALUES (new_vac_id, -1, to_date(startDate, 'YYYY-MM-DD'), id_position);

    INSERT INTO "Myronenko_O".staff ("Id_person", "Id_vacancy", date_in)
        VALUES (id_person, new_vac_id, to_date(startDate, 'YYYY-MM-DD'));
END;
$BODY$
LANGUAGE plpgsql;