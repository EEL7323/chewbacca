#!/bin/bash

sudo apt-get -y install python-pip python-dev
sudo pip install virtualenv
virtualenv flask
flask/bin/pip install -r requirements.txt
./db_teste_init.sh
