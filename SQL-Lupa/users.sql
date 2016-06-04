/* admin privileges */
CREATE USER admin WITH PASSWORD 'admin';
GRANT ALL PRIVILEGES ON DATABASE db_work TO admin;
GRANT ALL ON SCHEMA "Lupa_A" TO admin;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO admin;

/* operator privileges */
CREATE USER operator WITH PASSWORD 'operator';
GRANT ALL PRIVILEGES ON DATABASE db_work TO operator;
GRANT ALL ON SCHEMA "Lupa_A" TO operator;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO operator;
REVOKE INSERT, UPDATE, DELETE ON 
    "Lupa_A".actions,
    "Lupa_A".cards,
    "Lupa_A".doc_types,
    "Lupa_A".goods,
    "Lupa_A".action_program
    "Lupa_A".individ_contr_program FROM operator;

/* privileges for using views */
GRANT SELECT ON "Lupa_A".show_contractors TO admin, operator;
GRANT SELECT ON "Lupa_A".show_actions TO admin, operator;
GRANT SELECT ON "Lupa_A".show_actions TO admin, operator;
GRANT SELECT ON "Lupa_A".show_doc_types TO admin, operator;
GRANT SELECT ON "Lupa_A".show_good_types TO admin, operator;
GRANT SELECT ON "Lupa_A".left_goods TO admin, operator;
GRANT SELECT ON "Lupa_A".documents TO admin, operator;

/* privileges on "Myronenko_O" tables */
GRANT SELECT ON "Myronenko_O".staff TO admin, operator;
GRANT SELECT ON "Myronenko_O".person TO admin, operator;