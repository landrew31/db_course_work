CREATE OR REPLACE FUNCTION "Myronenko_O".delete_last_vacancy
    (IN id_position integer, IN proc_date VARCHAR)
RETURNS void AS
$BODY$
DECLARE
    opened_vac_count_by_position integer;
    last_date date;
BEGIN
    SELECT SUM(type) INTO opened_vac_count_by_position
        FROM "Myronenko_O".vacancies
        WHERE "Id_position" = id_position;
    IF opened_vac_count_by_position = 0
        THEN RAISE EXCEPTION 'wrong action';
    END IF;

    SELECT min(date) INTO last_date
        FROM (
            select * from "Myronenko_O".vacancies
	           where type = 1 and "Id_position" = id_position
	           order by date DESC
	           limit opened_vac_count_by_position ) as open_vacancies;
    IF last_date > to_date(proc_date, 'YYYY-MM-DD')
        THEN RAISE EXCEPTION 'wrong action';
    END IF;

    INSERT INTO "Myronenko_O".vacancies (type, date, "Id_position")
        VALUES (-1, to_date(proc_date, 'YYYY-MM-DD'), id_position);

END;
$BODY$
LANGUAGE plpgsql;
