#!flask/bin/python
from app import models, db
import datetime
import time
import sys

print >>sys.stderr, "Zerando o contador..."
C = models.Contador(0)
db.session.add(C)
db.session.commit()

print >>sys.stderr, "Inserindo usuarios..."
with open('db_data_init/db_user_init.txt') as f:
	for line in f:
		usuario,matricula,cardID,password,n_password = line.strip().split('|')
		U = models.User(usuario,matricula,cardID)
		U.hash_password(password)
		U.hash_n_password(n_password)
		T = models.Transaction(author=U,timestamp=datetime.datetime.utcnow(),event_id=0)
		db.session.add(U)
		db.session.add(T)
		db.session.commit()

print >>sys.stderr, "Inserindo Transacoes..."
with open('db_data_init/db_transaction_init.txt') as f:
	for line in f:
		usuario,eventID = line.strip().split()
		eventID = int(eventID)
		u = models.User.query.filter_by(username=usuario)[0]
		t = models.Transaction(author=u,timestamp=datetime.datetime.utcnow(),event_id=eventID)
		db.session.add(t)
		db.session.commit()
		time.sleep(1)
