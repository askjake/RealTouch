import socket
import subprocess
import json
import os
from tqdm import tqdm

# Function to get all subnets from ARP table
def get_subnets_from_arp():
	subnets = set()
	try:
		output = subprocess.check_output(['arp', '-a'], universal_newlines=True)
		output_lines = output.splitlines()
		for line in output_lines:
			if 'dynamic' in line:
				ip = line.split()[0]
				subnet = '.'.join(ip.split('.')[:-1])
				subnets.add(subnet)
	except subprocess.CalledProcessError:
		print("Failed to get subnets from ARP table.")
	return subnets

# Ask for the subnet to scan or option to scan all subnets from ARP table
subnet_option = input("Enter '1' to manually enter a subnet to scan, or '2' to scan all subnets from ARP table: ")
if subnet_option == '1':
	# Manual input of subnet to scan
	subnet = input("Enter the subnet to scan (e.g., 172.20.110): ")
elif subnet_option == '2':
	# Get subnets from ARP table
	subnets = get_subnets_from_arp()
	if len(subnets) > 0:
		print("Found subnets in ARP table: {}".format(', '.join(subnets)))
		subnet = None
		while subnet not in subnets:
			subnet = input("Enter one of the subnets to scan: ")
	else:
		print("No subnets found in ARP table.")
		exit()
else:
	print("Invalid option. Exiting.")
	exit()

# Load the JSON data from base.txt
with open('base.txt', 'r') as file:
	data = json.load(file)

# Loop through all possible host addresses in the subnet and check if each IP is responding before running get_stb_information.py

### Uncomment for proggress bar:
#for i in tqdm(range(1, 255), desc="Scanning IP addresses", unit="IP"):
for i in range(1, 255):

	ip = f"{subnet}.{i}"
	try:
		# Attempt to establish a connection to the IP address and port 443 with a timeout of 0.05 seconds
		sock = socket.create_connection((ip, 443), timeout=.05)
		sock.close()
		# If the connection is successful, run get_stb_information.py
		command = ["python", "get_stb_information.py", "-i", ip]
		output = subprocess.check_output(command, universal_newlines=True)
		output_lines = output.splitlines()
		rxid = None


		for line in output_lines:
			if line.startswith("rxid"):
				rxid = line.split()[1]
			if rxid is None:
				# Retry up to 3 times if rxid is not found
				for _ in range(3):
					command = ["python", "get_stb_information.py", "-i", ip]
					output = subprocess.check_output(command, universal_newlines=True)
					output_lines = output.splitlines()
					for line in output_lines:
						if line.startswith("rxid"):
							rxid = line.split()[1]
						if rxid is not None:
							break
					if rxid is not None:
						break
		if rxid is not None:
			stb_name = None
			for key, value in data.items():
				if isinstance(value, dict):
					if value["stb"] == rxid:
						stb_name = key
						break
			if stb_name is not None:
				print("stb_name: {}, IP: {}, rxid: {}".format(stb_name, ip, rxid))
			#else:
			#	print("IP: {}, rxid: {}".format(ip, rxid))
			# Rest of the code

		if rxid is not None:
			print("IP: {}, rxid: {}".format(ip, rxid))
			# Update the IP address in base.txt if it matches the rxid
			for key, value in data.items():
				if isinstance(value, dict):
					try:
						if value["stb"] == rxid and value["ip"] != ip:
							value["ip"] = ip
							print("Updated IP for {}: {}".format(key, ip))
							pass
					except KeyError:
						# Handle the case when "stb" key is not present in the dictionary
						print("KeyError: 'stb' not found in dictionary")
						pass
			# Write the updated JSON data back to base.txt
			with open('base.txt', 'w') as file:
				json.dump(data, file, indent=6)
	except (ConnectionRefusedError, socket.timeout):
		# If the connection fails or times out, skip it
		pass
