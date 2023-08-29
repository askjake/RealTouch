import argparse
import subprocess
import threading
import os
import json

# Define the path to where the script is, and  where base.txt is
path = r'C:\DPUnified\Tools\DishSendRESTCommand\scripts'
base_file = r'base.txt'
script = r'sgs_remote.py'
script_path = os.path.join(path, script)
base_path = os.path.join(path, base_file)
# print(path)
# print(os.path.join(path, script))
# print(os.path.join(path, base_file))
# print(base_path)


# Define the positional command-line argument
id = '-n'

# Load the JSON data from base.txt
with open(base_path, 'r') as file:
    data = json.load(file)

# Extract STB names from the 'base.txt' data
stb_names = list(data['stbs'].keys())

# Define a function to run the script with the positional argument for each STB name
def run_script(stb_name, command):
    # Show me the command that is running
    # Sprint(script_path, id, stb_name, command)
    # Run this command
    subprocess.run(['python', script_path, id, stb_name, command])
    # print(f'{stb_name}')

# Define the positional command-line argument to define 'command' in run_script()
parser = argparse.ArgumentParser(description='Run the script with the positional argument for each STB name')
parser.add_argument('command', type=str, nargs='?', default='Enter', help='the positional argument')
args = parser.parse_args()

# Create a list to store threads for running the script concurrently
threads = []

# Create and start a thread for each STB name
for stb_name in stb_names:
    thread = threading.Thread(target=run_script, args=(stb_name, args.command))
    threads.append(thread)
    thread.start()

# Wait for all threads to finish
for thread in threads:
    thread.join()

print('All STBs have been processed.')
################ DONE ################
