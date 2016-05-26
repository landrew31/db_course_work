CREATE USER admin WITH PASSWORD 'admin';
GRANT ALL PRIVILEGES ON DATABASE db_work TO admin;
GRANT ALL ON SCHEMA "Lupa_A" TO admin;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO admin;
GRANT SELECT ON "Lupa_A".show_contractors TO admin;
GRANT SELECT ON "Lupa_A".show_actions TO admin;
GRANT SELECT ON "Lupa_A".show_not_finished_actions_on_programs TO admin;
GRANT SELECT ON "Lupa_A".show_cards TO admin;
GRANT SELECT ON "Lupa_A".show_actions TO admin;

CREATE USER operator WITH PASSWORD 'operator';
GRANT ALL PRIVILEGES ON DATABASE db_work TO operator;
GRANT ALL ON SCHEMA "Lupa_A" TO operator;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO operator;
REVOKE INSERT, UPDATE, DELETE ON "Lupa_A".actions,
    "Lupa_A".cards,
    "Lupa_A".contractors,
    "Lupa_A".doc_types,
    "Lupa_A".entity_contr,
    "Lupa_A".individ_contr,
    "Lupa_A".action_programs FROM operator;
GRANT SELECT ON "Lupa_A".show_contractors TO operator;
GRANT SELECT ON "Lupa_A".show_actions TO operator;
GRANT SELECT ON "Lupa_A".show_not_finished_actions_on_programs TO operator;
GRANT SELECT ON "Lupa_A".show_cards TO operator;
GRANT SELECT ON "Lupa_A".show_programs TO operator;
