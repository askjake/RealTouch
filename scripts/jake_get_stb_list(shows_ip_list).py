import socket
import subprocess
import json
import os
from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor, as_completed


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


subnets = get_subnets_from_arp()
if len(subnets) > 0:
	print("Found subnets in ARP table: {}".format(', '.join(subnets)))
	subnet = None
	while subnet not in subnets:
		subnet = input("Enter one of the subnets to scan: ")
else:
	print("No subnets found in ARP table.")
	exit()

# Load the JSON data from base.txt
with open('base.txt', 'r') as file:
	data = json.load(file)

# Create a list to store all IPs found
ip_list = []

# Loop through all possible host addresses in the subnet and check if each IP is responding
for i in tqdm(range(1, 255), desc="Scanning IP addresses", unit="IP"):
	ip = f"{subnet}.{i}"
	try:
		# Attempt to establish a connection to the IP address and port 443 with a timeout of 0.05 seconds
		sock = socket.create_connection((ip, 443), timeout=.05)
		sock.close()
		# If the connection is successful, add the IP to the ip_list
		ip_list.append(ip)

	except (ConnectionRefusedError, socket.timeout):
		# If the connection fails or times out, skip it
		pass
		
# Print the ip_list in a column
print("IP List:")
for ip in ip_list:
    print(ip)
		
# Loop through the ip_list and run get_stb_information.py for each IP

# Process all IPs concurrently using multi-threading
with ThreadPoolExecutor(max_workers=20) as executor:
    futures = [executor.submit(process_ip, ip) for ip in ip_list]
    


for ip in ip_list:
	try:
		# Run get_stb_information.py command for the IP
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
	except Exception as e:
		print("Error occurred: {}".format(e))
