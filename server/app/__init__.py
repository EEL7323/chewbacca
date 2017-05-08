import os
import sys

from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
if os.path.join('../config.py'):
	print >>sys.stderr, "Reading config file from config.py" 
	app.config.from_object('config')

db = SQLAlchemy(app)

from app import views, models
