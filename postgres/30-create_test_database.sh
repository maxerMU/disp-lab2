#!/usr/bin/env bash
set -e

# psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < scripts/db-v3.sql
export SCRIPT_PATH=/docker-entrypoint-initdb.d/
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < $SCRIPT_PATH/cars/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < $SCRIPT_PATH/payments/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < $SCRIPT_PATH/rentals/crete_tables.sql
psql "user=postgres hostaddr=127.0.0.1 port=5432 password=postgres" < $SCRIPT_PATH/cars/insert_test_car.sql