CREATE OR REPLACE VIEW show_good_types AS SELECT
  good_name,
  price_per_one,
  term,
  item
FROM 
  "Lupa_A".goods; 