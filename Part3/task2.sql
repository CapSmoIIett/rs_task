SELECT COUNT(*) / 7.0 AS average_logins_per_day
FROM players
WHERE 
  login_time >= CURRENT_DATE - 6 
  AND login_time < CURRENT_DATE + 1;
  
