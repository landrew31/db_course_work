CREATE USER admin WITH PASSWORD 'admin';
GRANT ALL PRIVILEGES ON DATABASE db_work TO admin;
GRANT ALL ON SCHEMA "Lupa_A" TO admin;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO admin;

CREATE USER operator WITH PASSWORD 'operator';
GRANT ALL PRIVILEGES ON DATABASE db_work TO operator;
GRANT ALL ON SCHEMA "Lupa_A" TO admin;
GRANT USAGE, SELECT ON SEQUENCE inc_primary TO admin;
REVOKE INSERT, UPDATE, DELETE ON "Lupa_A".actions, 
    "Lupa_A".cards, 
    "Lupa_A".contractors, 
    "Lupa_A".doc_types, 
    "Lupa_A".entity_contr, 
    "Lupa_A".individ_contr FROM operator;
