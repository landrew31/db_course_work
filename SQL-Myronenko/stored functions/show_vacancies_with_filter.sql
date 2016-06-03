CREATE OR REPLACE FUNCTION "Myronenko_O".show_vacancies_with_filter(
    IN show_active BOOL
)
RETURNS TABLE * AS
$BODY$
BEGIN
 IF show_active
 THEN
 RETURN QUERY SELECT
   *
   From view_vacancies.sql
 ELSE
 END IF;
 END;
$BODY$
LANGUAGE plpgsql;
