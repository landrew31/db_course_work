CREATE USER admin WITH PASSWORD 'admin';
GRANT ALL PRIVILEGES ON DATABASE db_work TO admin;
GRANT ALL ON SCHEMA "Myronenko_O" TO admin;
GRANT SELECT ON "Myronenko_O".show_persons TO admin;

CREATE USER hr_operator WITH PASSWORD 'hr_operator';
GRANT ALL PRIVILEGES ON DATABASE db_work TO hr_operator;
GRANT ALL ON SCHEMA "Myronenko_O" TO hr_operator;
GRANT SELECT ON "Myronenko_O".show_persons TO hr_operator;

-- GRANT USAGE, SELECT ON SEQUENCE inc_primary TO hr_operator;
-- REVOKE INSERT, UPDATE, DELETE ON "Myronenko_O".actions,
--     "Lupa_A".cards,
--     "Lupa_A".contractors,
--     "Lupa_A".doc_types,
--     "Lupa_A".entity_contr,
--     "Lupa_A".individ_contr,
--     "Lupa_A".action_programs FROM operator;
-- GRANT SELECT ON "Lupa_A".show_contractors TO operator;
-- GRANT SELECT ON "Lupa_A".show_actions TO operator;
-- GRANT SELECT ON "Lupa_A".show_not_finished_actions_on_programs TO operator;
-- GRANT SELECT ON "Lupa_A".show_cards TO operator;
