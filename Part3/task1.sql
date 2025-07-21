SELECT device, COUNT(*) as logins_count
FROM players
GROUP BY device
ORDER BY login_count DESC
LIMIT 5;
