from app import db
from passlib.apps import custom_app_context as pwd_context
import datetime

class User(db.Model):
	__tablename__ = 'user'
	id = db.Column(db.Integer, primary_key=True)
	username = db.Column(db.String(64), index=True, unique=True)
	password = db.Column(db.String(120))
	cardID = db.Column(db.String(256))
	registered_on = db.Column(db.DateTime)
	transactions = db.relationship('Transaction', backref='author', lazy='dynamic')
	
	def __init__(self, username, cardID):
		self.username = username
		self.cardID = cardID
		self.registered_on = datetime.datetime.utcnow()

	def hash_password(self, password):
		self.password = pwd_context.encrypt(password)

	def verify_password(self, password):
		return pwd_context.verify(password,self.password)

	def __str__(self):
		return '<User - Username:{self.username}, CardID:{self.cardID}>'.format(**locals())

class Transaction(db.Model):
	__tablename__ = 'transaction'
	id = db.Column(db.Integer, primary_key=True)
	user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
	timestamp = db.Column(db.DateTime)
	event_id = db.Column(db.Integer)
	
	def __str__(self):
		return "<Transaction - Type:{self.event_id}, UserID={self.user_id}>".format(**locals())

