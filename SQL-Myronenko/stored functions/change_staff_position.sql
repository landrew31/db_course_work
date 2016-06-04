CREATE OR REPLACE FUNCTION "Myronenko_O".change_staff_position
    (IN id_person integer,
    IN id_staff integer,
    IN id_new_position integer,
    IN change_date VARCHAR)
RETURNS void AS
$BODY$
BEGIN

    EXECUTE "Myronenko_O".fire_staff(
        id_staff,
        change_date);

    EXECUTE "Myronenko_O".add_person_on_position(
        id_person,
        id_new_position,
        change_date);

END;
$BODY$
LANGUAGE plpgsql VOLATILE;
