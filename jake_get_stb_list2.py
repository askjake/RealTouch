import socket
import subprocess
import json
from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor, as_completed

def do_ips(ip):
    print("do_ips: {}\n".format(ip))
    try:
        # Run get_stb_information.py command for the IP
        command = ["python", "get_stb_information.py", "-i", ip]
        rxid = None
        for _ in range(3): # initial try + 3 retries
            output = subprocess.check_output(command, universal_newlines=True)
            for line in output.splitlines():
                if line.startswith("rxid"):
                    rxid = line.split()[1]
                    break
            if rxid:
                break

        if rxid:
            for remote_key, remote_data in data["stbs"].items():
                if remote_data["stb"] == rxid:
                    # Update IP in the data dictionary for the matching rxid
                    remote_data["ip"] = ip
                    print("Updated IP for {}: IP: {}, rxid: {}\n".format(remote_key, ip, rxid))
                    break
            else:
                print(f"No matching remote found for rxid: {rxid}. IP: {ip}")

    except Exception as e:
        print("Error occurred: {}".format(e))

def get_subnets_from_arp():
	subnets = set()
	try:
		output = subprocess.check_output(['arp', '-a'], universal_newlines=True)
		for line in output.splitlines():
			if 'dynamic' in line:
				ip = line.split()[0]
				subnet = '.'.join(ip.split('.')[:-1])
				subnets.add(subnet)
	except subprocess.CalledProcessError:
		print("Failed to get subnets from ARP table.")
	return subnets

subnets = get_subnets_from_arp()

if not subnets:
	print("No subnets found in ARP table.")
	exit()

print("Found subnets in ARP table: {}".format(', '.join(subnets)))

with open('base.txt', 'r') as file:
	data = json.load(file)

ip_list = []

# Discover available IPs
for subnet in subnets:
	for i in tqdm(range(1, 255), desc="Scanning IP addresses", unit="IP"):
		ip = f"{subnet}.{i}"
		try:
			sock = socket.create_connection((ip, 443), timeout=.01)
			sock.close()
			ip_list.append(ip)
		except (ConnectionRefusedError, socket.timeout):
			pass

print("IP List:")
print("\n".join(ip_list))

# Process all IPs concurrently
with ThreadPoolExecutor(max_workers=20) as executor:
	futures = [executor.submit(do_ips, ip) for ip in ip_list]
	for future in as_completed(futures):
		pass
        
with open('base.txt', 'w') as file:
	json.dump(data, file, indent=4)