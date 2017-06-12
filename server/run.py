#!flask/bin/python
import argparse
from app import app
import sys

if __name__ == '__main__':
	reload(sys)
	sys.setdefaultencoding('utf-8')
	parser = argparse.ArgumentParser(description='Inicia o servidor')

	parser.add_argument('--host', type=str, action='store',
						help='Server Host', default='127.0.0.1')
	parser.add_argument('--port', type=int, action='store',
						help='Server Port', default=5000)

	args = parser.parse_args()
	
	app.run(host=args.host,port=args.port,debug=True)
