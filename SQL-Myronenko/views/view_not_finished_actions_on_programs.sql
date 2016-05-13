CREATE OR REPLACE VIEW show_not_finished_actions_on_programs AS SELECT 
  * FROM (SELECT
  pro.program_name,
  string_agg(act.action_name, ',')
FROM 
  action_programs pro,
  actions act
WHERE act."Id_action" = ANY (actions_on_program) 
GROUP BY
  pro.program_name) AS foo;