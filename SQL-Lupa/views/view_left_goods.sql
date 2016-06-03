CREATE OR REPLACE VIEW left_goods AS SELECT
  good_name,
  price_per_one,
  term,
  "Lupa_A".count_goods("Id_goods")
FROM 
  "Lupa_A".goods;