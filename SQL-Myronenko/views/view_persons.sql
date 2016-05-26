CREATE OR REPLACE VIEW "Myronenko_O".show_persInfo
AS SELECT
  per_name,
  per_surname,
  education
FROM
  "Myronenko_O".person;
