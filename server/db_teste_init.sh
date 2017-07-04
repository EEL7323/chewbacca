#/bin/bash

[ -f app/views.pyc ] && rm app/views.pyc
[ -f app/models.pyc ] && rm app/models.pyc
[ -f app.db ] && rm app.db
[ -d db_repository ] && rm -r db_repository
./db_create.py
./db_migrate.py
./db_populate.py
