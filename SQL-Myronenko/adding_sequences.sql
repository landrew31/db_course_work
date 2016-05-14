CREATE SEQUENCE "Myronenko_O".inc_primary
  INCREMENT 1
  MINVALUE 1
  MAXVALUE 92223
  START 1
  CACHE 1;

ALTER TABLE "Myronenko_O".person ALTER COLUMN "Id_person" SET DEFAULT nextval('inc_primary'::regclass);

ALTER TABLE "Lupa_A".cards ALTER COLUMN "Id_card" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".contractors ALTER COLUMN "Id_contr" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".doc_types ALTER COLUMN "Id_doctype" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".documentation ALTER COLUMN "Id_doc" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".entity_contr ALTER COLUMN "Id_ent" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".goods ALTER COLUMN "Id_goods" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".goods_moves ALTER COLUMN "Id_move" SET DEFAULT nextval('inc_primary'::regclass);
ALTER TABLE "Lupa_A".individ_contr ALTER COLUMN "Id_ind" SET DEFAULT nextval('inc_primary'::regclass);
