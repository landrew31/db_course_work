CREATE OR REPLACE FUNCTION "Myronenko_O".change_staff_position
    (IN id_person integer, IN id_staff integer, IN id_new_position integer)
RETURNS void AS
$BODY$
BEGIN

    EXECUTE "Myronenko_O".fire_staff(
        id_staff,
        to_char(current_date, 'YYYY-MM-DD'));

    EXECUTE "Myronenko_O".add_person_on_position(
        id_person,
        id_new_position,
        to_char(current_date, 'YYYY-MM-DD'));

END;
$BODY$
LANGUAGE plpgsql VOLATILE;
