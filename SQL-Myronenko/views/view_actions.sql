CREATE OR REPLACE VIEW show_actions AS SELECT
  action_name,
  percent,
  day_start,
  day_stop
FROM 
  "Lupa_A".actions; 