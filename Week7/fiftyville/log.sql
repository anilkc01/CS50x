-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street"; --read the descriptionn of the casee

SELECT transcript FROM interviews WHERE month = 7 AND day = 28; -- to read what we got from interview


-- to check which license platee number went out from bakeery at that time --
SELECT * FROM people  WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit");



-- To check who withdraw money from leggett street atm --
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));


-- To check who made phone call on that day for less than a minute --
SELECT * FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60);


-- To check the list of peoples in the earliest flight out of Fiftyville ---
SELECT * FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE month = 7 AND day = 29  AND origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville") ORDER by hour LIMIT 1));



-- To Find the actual guy behind it, one who fits in all case, ATM, Bakery, call and first flight --
SELECT * FROM people  WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit")
 AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60)
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights WHERE month = 7 AND day = 29  AND origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville") ORDER by hour LIMIT 1));


-- To check the destination of that flight --
SELECT city FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE month = 7 AND day = 29  AND origin_airport_id IN
(SELECT id FROM airports WHERE city = "Fiftyville") ORDER by hour LIMIT 1);

-- To  check who helped him --
SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM people WHERE name ="Bruce"));
