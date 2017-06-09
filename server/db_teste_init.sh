#/bin/bash

rm app.db
rm -r db_repository/
./db_create.py
./db_migrate.py
./db_populate.py
