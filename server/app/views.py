# -*- coding: utf-8 -*-
import json
import datetime

from models import *
from app import app, db
from functools import wraps
from flask import jsonify, request, abort, render_template, flash, url_for, redirect

@app.route('/contador', methods=['GET', 'POST'])
def contador():
	"""
	Obtem ou altera a contagem atual de pessoas no RU
	"""
	C = Contador.query.filter_by(id=1).first()
	if request.method == "GET":
		v = C.v
		timestamp = C.timestamp
		obj = {"contador" : v , "timestamp" : timestamp}
		return jsonify([obj])
	else:
		if not request.json or not 'v' in request.json:
			abort(400)
		else:
			Contador.query.filter_by(id=1).update({"v":request.json['v'], "timestamp":datetime.datetime.utcnow()},synchronize_session=False)
			db.session.commit()
			return ('', 201)

@app.route('/transaction', methods=['GET'])
def transaction():
	"""
	Retorna todas as transações armazenadas num json
	"""
	J = []
	for i,item in enumerate(Transaction.query.all(),1):
		user_id = item.user_id
		event = item.event_id
		timestamp = item.timestamp
		U = User.query.filter_by(id=user_id)[0]
		username = U.username
		cardid = U.cardID
		n_password_hash = U.n_password_hash
		salt = U.salt_n_password
		matricula = U.matricula
		obj = {"salt":salt,"matricula":matricula,"n_password_hash":n_password_hash, "user_id":user_id,"event":event, "timestamp":timestamp, "username":username, "cardID": cardid}
		J.append(obj)
	return jsonify(J)

@app.route('/transaction/<int:user_id>', methods=['GET','POST'])
def transaction_user(user_id):
	""" 
	GET - Retorna todas as transacoes do usuario num json
	POST - Adiciona uma transacao ao usuario user_id
		Chaves Json necessárias:
			-> "event_id": int - deve indicar a quantidade de creditos da transacao
	"""
	if request.method == "GET":
		J = []
		for i,item in enumerate(Transaction.query.filter_by(user_id=user_id),1):
			user_id = item.user_id
			event = item.event_id
			timestamp = item.timestamp
			U = User.query.filter_by(id=user_id)[0]
			username = U.username
			cardid = U.cardID
			n_password_hash = U.n_password_hash
			salt = U.salt_n_password
			matricula = U.matricula
			obj = {"salt":salt,"matricula":matricula,"n_password_hash":n_password_hash,"user_id":user_id,"event":event, "timestamp":timestamp,"username":username, "cardID": cardid}
			J.append(obj)
		return jsonify(J)
	else:
		if not request.json or not 'event_id' in request.json:
			abort(400)
		else:
			u = User.query.filter_by(id=user_id)[0]
			t = Transaction(author=u,timestamp=datetime.datetime.utcnow(),event_id=request.json['event_id'])
			
			try:
				db.session.add(t)
				db.session.commit()
				return ('', 201)
			except Exception as e:
				db.session.rollback()
				return ("", 400)

@app.route('/user/id/card/<cardid>', methods=['GET'])
def get_userid_from_cardid(cardid):
	u = User.query.filter_by(cardID=cardid).first()
	if u == None:
		obj = {"user_id":-1}
	else:
		obj = {"user_id":u.id}
	return jsonify(obj)

@app.route('/user/id/username/<username>', methods=['GET'])
def get_userid_from_username(username):
	u = User.query.filter_by(username=username).first()
	if u == None:
		obj = {"user_id":-1}
	else:
		obj = {"user_id":u.id}
	return jsonify(obj)


@app.route('/user', methods=['POST'])
def new_user():
	""" 
	POST - Adiciona um usuario
		Chaves Json necessárias:
			-> "username": string - um nome de usuario
			-> "password"   : string - senha do usuario
	"""
	required_data = set(["username", "password", "n_password", "cardID"])
	if not request.json or not all([x in required_data for x in request.json.keys()]):
		abort(400)
	else:
		username = request.json.get('username')
		password = request.json.get('password')
		n_password = request.json.get('n_password')
		cardID   = request.json.get('cardID')

		if username is None or password is None or n_password is None or cardID is None:
			print "Json invalido, algum valor eh nulo"
			abort(400)
		if User.query.filter_by(username = username).first() is not None:
			print "Usuario ja existe"
			abort(400)
		u = User(username, cardID)
		u.hash_password(password)
		u.hash_n_password(n_password)
		print "Criando usuario"
		try:
			print "Commit usuario"
			db.session.add(u)
			db.session.commit()
			return ("", 201)
		except Exception as e:
			print "ERRO"
			db.session.rollback()
			return ("",400)

@app.route('/user/<int:user_id>', methods=['GET'])
def user_user(user_id):
	if request.method == "GET":
		u = User.query.filter_by(user_id = user_id).first()

@app.route('/echo', methods=['POST'])
def echo():
	required_data = set(["key1","key2"])
	if not request.json or not  all([x in required_data for x in request.json.keys()]):
		return ("JSON INVALIDO",400)
	else:
		key1 = request.json.get('key1')
		key2 = request.json.get('key2')
		return "Enviado:\nkey1={key1}\nkey2={key2}\n".format(**locals())

@app.route('/')
def index():
    return 'Hello, world!'

