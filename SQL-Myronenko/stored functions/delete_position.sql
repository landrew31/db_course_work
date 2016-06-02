CREATE OR REPLACE FUNCTION "Myronenko_O".delete_position
    (IN id_position integer)
RETURNS void AS
$BODY$
DECLARE
    staff_count_by_position integer;
    opened_vac_count_bu_posit integer;
    iterator integer;
BEGIN
    SELECT count(*) into staff_count_by_position
    FROM
        "Myronenko_O".staff staff
        join "Myronenko_O".vacancies vacancies
            on staff."Id_vacancy" = vacancies."Id_vacancy"
    WHERE
      staff.date_out IS NOT NULL AND
      vacancies."Id_position" = id_position;
    IF staff_count_by_position > 0
        THEN RAISE EXCEPTION 'impossible action';
    END IF;

    SELECT SUM(type) INTO opened_vac_count_bu_posit
        FROM "Myronenko_O".vacancies
        WHERE "Id_position" = id_position;
    SELECT 0 INTO iterator;
    WHILE iterator < opened_vac_count_bu_posit
        LOOP
            iterator := iterator + 1;
            SELECT "Myronenko_O".delete_last_vacancy(id_position, current_date);
        END LOOP;

    UPDATE "Myronenko_O".positions
        SET exists = FALSE
        WHERE "Id_position" = id_position;

END;
$BODY$
LANGUAGE plpgsql;
