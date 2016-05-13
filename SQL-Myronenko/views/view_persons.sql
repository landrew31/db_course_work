CREATE OR REPLACE VIEW show_persons AS SELECT
  per_name,
  per_surname,
  education
FROM
  "Myronenko_O".person;
