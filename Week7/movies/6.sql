SELECT AVG(rating) AS average FROM ratings WHERE  movie_id IN (SELECT id from movies where year = 2012);
