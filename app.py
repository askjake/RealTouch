from flask import Flask, request, jsonify, send_from_directory
from flask import Flask, render_template

import subprocess
import os
import json
import shlex
import sys
import fcntl, socket, struct
import argparse
import requests
from uuid import getnode as get_mac
import serial
import serial.tools.list_ports
from sgs_pair import *
from sgs_remote import *



DEFAULT_RECEIVER = "R0000000000-00"
BASE_FILE_NAME = "base.txt"
BASE_FILE_PATH = os.path.join(os.path.dirname(sys.argv[0]), BASE_FILE_NAME)
base = None
if os.path.isfile(BASE_FILE_PATH):
	with open(BASE_FILE_PATH) as f:
		base = json.load(f)


class SerialConnection:
	def __init__(self, port='COM4', baudrate=115200):
		self.port = port
		self.baudrate = baudrate
		self.connection = None

	def connect(self):
		try:
			if not self.connection:
				self.connection = serial.Serial(self.port, self.baudrate)
		except serial.SerialException as e:
			print(f"Failed to connect to {self.port}. Error: {e}")


	def disconnect(self):
		if self.connection:
			self.connection.close()
			self.connection = None

	def send_command(self, cmd):
		self.connect()
		print(f'Sending command: {cmd} via serial port {self.port}')
		time.sleep(.1)
		while self.connection.out_waiting > 0:
			time.sleep(0.1)
		self.connection.write(f"{cmd}\n".encode('utf-8'))
		print(f'sending: {cmd}')

		output = ""
		while self.connection.in_waiting > 0:
			output += self.connection.read(self.connection.in_waiting).decode('utf-8')
		return output

app = Flask(__name__)  # create an instance of the Flask class
@app.route('/')
def serve_app():
	return send_from_directory('.', 'app.html')

@app.route('/getComPorts', methods=['GET'])
def get_com_ports():
	print(f'getting ports: ')  # Debug print
	ports = [port.device for port in serial.tools.list_ports.comports()]
	print(f'Available ports: {ports}')
	return jsonify(ports)

@app.route('/images')
def get_remote():
	return app.send_static_file('\54.1.jpg')


@app.route('/serial')
def serial_page():
	return send_from_directory('./Serial', 'serial.html')

@app.route('/serial/site.css')
def serial_site_css():
	return send_from_directory('./Serial', 'site.css')

@app.route('/serial/serial.js')
def serial_js():
	return send_from_directory('./Serial', 'serial.js')

@app.route('/serial/site.js')
def serial_site_js():
	return send_from_directory('./Serial', 'site.js')

@app.route('/base.txt')
def base_txt():
	return send_from_directory('.', 'base.txt')
	
@app.route('/54.jpg')
def remote_jpg():
	return send_from_directory('.', '54.jpg')	
	
@app.route('/base')
def serve_app_page():
	return send_from_directory('.', 'base.html')

@app.route('/getStb', methods=['GET'])
def get_stb():
	# Ensure base is loaded
	if base is None or 'stbs' not in base:
		return jsonify({}), 400  # Return error if base isn't loaded

	stbs = base['stbs']
	return jsonify(stbs)
@app.route('/54/<remote>/<com>/<button_id>', methods=['GET', 'POST'])
def handle_button_command(remote, com, button_id):
	try:
		#com = 'COM7' # Define the COM port you're using
		#stb = 'remote 04' # Define the STB you're using
		cmd = button_id # Define the command you want to send
		ser = serial.Serial(com, 115200)
		print(f'Sending command: {cmd} to {remote} via serial port {com}')  # Debug print

		# Write the command
		time.sleep(.1)
		while ser.out_waiting > 0:
			time.sleep(0.1)
		ser.write(f"{remote} {cmd}\n".encode('utf-8'))
		
		time.sleep(1.8)
		ser.write(f"{cmd}\n".encode('utf-8'))
		print(f'sending: {cmd}')

		output = ""
		while ser.in_waiting > 0:
			output += ser.read(ser.in_waiting).decode('utf-8')

		#Close the serial port
		ser.close()
		cmd = button_id
		output = conn.send_command(cmd)
		return jsonify({'output': output})
	except Exception as e:
		return jsonify({'error': str(e)})
		

@app.route('/run_script/<stb>/<sgs>/<rf>/<button_id>', methods=['GET', 'POST'] )
def run_script(stb, sgs, rf, button_id):
	settings = load_settings()
	stb_settings = settings.get('stbs', {}).get(stb)

	output = ""
	# Convert the string arguments to boolean values
	sgs = (sgs.lower() == 'true')
	rf = (rf.lower() == 'true')
	

   
		# Construct the command
	if sgs:
		cmd = ['python', 'sgs_remote.py', '-n', stb, button_id]
		print(f'Running command: {cmd}')  # Debug print
		result = subprocess.run(cmd, capture_output=True, text=True)
		output = result.stdout
		error = result.stderr
	elif rf:
		button_id = button_id.replace(" ", "_")
		if button_id == 'remote_select':
			button_id = stb
		cmd = button_id
		print(f'Sending command: {cmd} to {stb} via serial port {com}')  # Debug print
		# Open a connection to the serial port
		try:
			ser = serial.Serial(com, 115200)
			print(f' Running serial command: {button_id}')  # Debug print

			# Write the command
			
			time.sleep(.1)
			while ser.out_waiting > 0:
				time.sleep(0.1)
			ser.write(f"{stb} {cmd}\n".encode('utf-8'))
			print(f' sending: {stb}')
			time.sleep(1.5)
			ser.write(f"{cmd}\n".encode('utf-8'))
			print(f' sending: {cmd}')
			#ser.write(f"3\n".encode('utf-8'))
			output = ""
			while ser.in_waiting > 0:
				output += ser.read(ser.in_waiting).decode('utf-8')
			# Close the serial port
			ser.close()
			output = conn.send_command(cmd) 
			return jsonify({'output': output})
		except Exception as e:
			output = str(e)

	return jsonify({'output': output})

@app.route('/save_settings', methods=['POST'])
def sgs_save_base():
	global base
	if base is None:
		base = {}  # Initialize base as an empty dictionary if it's None
	data = request.json
	base['stbs'] = data['stbs']
	base['stb'] = data.get('stb')  # This will not raise a KeyError if 'stb' is not found in data
	base['ip'] = data.get('ip')
	base['com'] = data.get('com')
	with open(BASE_FILE_PATH, 'w') as outfile:
		json.dump(base, outfile, indent=2)
	return 'ok'

def load_settings():
	with open('base.txt', 'r') as file:
		data = json.load(file)
	stbs_data = data['stbs']
	return stbs_data  # return the data as a dictionary

@app.route('/load', methods=['GET'])
def get_settings():
	stbs_data = load_settings()
	return jsonify(stbs_data)  # return the data as a Flask Response object


# load STBs info from base file
@app.route('/settings')
def sgs_load_base():
	base = None
	base_path = os.path.join(os.path.dirname(sys.argv[0]), BASE_FILE_NAME)
	if not os.path.isfile(base_path):
		return jsonify({'error': f"Cannot open {base_path}"}), 500  # Return error if file doesn't exist

	try:
		with open(base_path) as f:
			base = json.load(f)
	except Exception as e:
		return jsonify({'error': f"Error loading base: {repr(e)}"}), 500  # Return error if unable to load JSON

	base_filtered = {'stbs': {}}

	if base is not None and 'stbs' in base:
		for key, value in base['stbs'].items():
			base_filtered['stbs'][key] = {
				'stb': value.get('stb', ''),
				'ip': value.get('ip', ''),
				'prod': value.get('prod', ''),
				'lname': value.get('lname', ''),
				'passwd': value.get('passwd', ''),
				'com': value.get('com', ''),
			}
	
	return jsonify(base_filtered)
	
@app.route('/sgs_pair_start/<stb>/<ip>', methods=['POST'])
def start_pairing_route(stb, ip):
	print(f'Start pairing with stb={stb} and ip={ip}')
	# Start the pairing process
	stb_obj = start_pairing(stb, ip)
	print(f'Stb_obj returned by start_pairing is {stb_obj}')
	# handle stb_obj as required
	return jsonify({'output': 'pairing started'})

@app.route('/sgs_pair_finish/<stb>/<ip>/<pin>', methods=['POST'])
def finish_pairing_route(stb, ip, pin):
	print(f'Finish pairing route called with stb={stb}, ip={ip}, and pin={pin}')
	finish_pairing(stb, ip, pin)
	return jsonify({'output': 'pairing finished'})



	return jsonify({'output': 'pairing completed'})




if __name__ == '__main__':
	app.run(host = '127.0.0.1', port=5001, debug=True)
