#!flask/bin/python
import argparse
from app import app

if __name__ == '__main__':

	parser = argparse.ArgumentParser(description='Inicia o servidor')

	parser.add_argument('--host', type=str, action='store',
						help='Server Host', default='127.0.0.1')

	args = parser.parse_args()

	app.run(host=args.host,debug=True)