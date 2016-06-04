-- admin
CREATE USER admin WITH PASSWORD 'admin';
GRANT ALL PRIVILEGES ON DATABASE db_work TO admin;
GRANT ALL ON SCHEMA "Myronenko_O" TO admin;


-- hr_operator
CREATE USER hr_operator WITH PASSWORD 'hr_operator';
GRANT ALL PRIVILEGES ON DATABASE db_work TO hr_operator;
GRANT ALL ON SCHEMA "Myronenko_O" TO hr_operator;

GRANT ALL ON TABLE "Myronenko_O".absence_type TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".absences TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".neccessary_skills TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".person TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".personal_skills TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".skills TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".staff TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".timeschedule TO hr_operator;
GRANT ALL ON TABLE "Myronenko_O".vacancies TO hr_operator;
GRANT SELECT ON TABLE "Myronenko_O".positions TO hr_operator;
