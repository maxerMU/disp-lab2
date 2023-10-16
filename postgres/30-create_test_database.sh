#!/usr/bin/env bash
set -e

psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < scripts/db-v3.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < cars/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < payments/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < rentals/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < cars/insert_test_car.sql