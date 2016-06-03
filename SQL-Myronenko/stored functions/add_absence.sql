CREATE OR REPLACE FUNCTION "Myronenko_O".add_absence
   (IN id_staff INTEGER,
    IN date_in_s VARCHAR,
    IN date_out_s VARCHAR,
    IN abs_type INTEGER,
    IN descr VARCHAR)
RETURNS void AS
$BODY$
DECLARE
    date_in date;
    date_out date;
BEGIN

    SELECT to_date(date_in_s, 'YYYY-MM-DD') INTO date_in;
    SELECT to_date(date_out_s, 'YYYY-MM-DD') INTO date_out;

    INSERT INTO "Myronenko_O".absences ("Id_stuff", date_in, date_out, "Id_abs_type", description)
        VALUES (id_staff, date_in, date_out, abs_type, descr);

END;
$BODY$
LANGUAGE plpgsql;
