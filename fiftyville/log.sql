-- Keep a log of any SQL queries you execute as you solve the mystery.

--Theif = Luca
--Escaped to = New York City
--Accomplice = Kathyrn

------------------
--query #1: read crime report description
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street" AND month = 7 AND day = 28;

--query 1 result: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
--Littering took place at 16:36. No known witnesses.

--------------------

--query #2: (read bakery_security_log based on hour, minute, day, month, year; print activity and license plate)
SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, bakery_security_logs.hour, bakery_security_logs.minute, people.name
FROM bakery_security_logs
FULL OUTER JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = "exit";

--Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey, Taylor


---------------------------------------------------------------

--query 3 (Read transcripts and names from interview table using date and time)
SELECT id, name, transcript
FROM interviews
WHERE month = 7 AND day = 28;


-------------------------------------------------------------------

--query 4 atm transactions
SELECT atm_transactions.account_number, people.name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.atm_location = "Leggett Street" AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw";

-- Bruce, Luca, Iman, Diana, Taylor

----------------------------------------------------------------------

--query 5 bank accounts
SELECT bank_accounts.account_number, people.name, people.phone_number, people.passport_number, people.license_plate
FROM bank_accounts
FULL OUTER JOIN people ON bank_accounts.person_id = people.id
WHERE people.license_plate = "4328GD8" OR people.license_plate = "G412CB7" OR people.license_plate = "L93JTIZ" OR people.license_plate = "322W7JE" OR people.license_plate = "0NTHK55";


--------------------------------------------------------------------------

--query 6 airport info; join airports, flights, and passengers
SELECT flights.origin_airport_id, flights.destination_airport_id, airports.city, airports.id, flights.hour, flights.minute, people.name
FROM passengers
JOIN airports ON flights.origin_airport_id = airports.id
JOIN flights ON passengers.flight_id = flights.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE (airports.city = "Fiftyville" AND flights.month = 7 AND flights.day = 29);

--query 6.5
SELECT city, id
FROM airports
WHERE airports.id = 8 OR airports.id = 4 OR airports.id = 6;

--Bruce, Luca, Taylor

------------------------------------------------------------

--Query 7 find the accomplice by searching phone records for 10:15, duration <1 minute, join phone calls and people
SELECT phone_calls.caller, people.name,  phone_calls.receiver, phone_calls.duration
FROM phone_calls
FULL OUTER JOIN people ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND duration <= 60;

SELECT phone_calls.caller, people.name,  phone_calls.receiver, phone_calls.duration
FROM phone_calls
FULL OUTER JOIN people ON phone_calls.receiver = people.phone_number
WHERE month = 7 AND day = 28 AND duration <= 60;

--Bruce and Robin or Taylor and James