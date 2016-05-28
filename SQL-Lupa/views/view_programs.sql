CREATE OR REPLACE VIEW show_programs AS SELECT
  program_name,
  day_start,
  day_stop
FROM 
  "Lupa_A".programs; 