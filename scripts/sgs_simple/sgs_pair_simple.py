#!/usr/bin/env python3
#
# pair PC to STB as a 3rd party device
#
# run for help:
#  ./sgs_pair_simple.py -h
#
# Example
#  ./sgs_pair_simple.py -m 9c7bef372fef -r XS99c7bef372fef -s R1911703199-05 -i 192.168.1.115
#

from time import sleep
import sys
import argparse
import os
import json
import requests
from requests.auth import HTTPDigestAuth
from uuid import getnode as get_mac

# to remove warnings export the following bash env
# export PYTHONWARNINGS="ignore:Unverified HTTPS request"


# defaul values
MAC = ''.join(['{:02x}'.format((get_mac() >> i) & 0xff) for i in range(0, 8*6, 8)][::-1])
AID = 'S9'

# get params
parser = argparse.ArgumentParser(description="send IR keys over SGS",
      epilog =
      '''
Example:
./sgs_pair_simple.py -s R1911703199-05 -i 192.168.1.115

Note, the Python may print warnings about non-registered certificate.
to remove warnings export the following bash env
export PYTHONWARNINGS="ignore:Unverified HTTPS request"
      ''',
                                 formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("-i", "--ip", help="specify STB IP", required=True)
parser.add_argument("-s", "--stb", help="specify STB receiver ID", required=True)
parser.add_argument("-m", "--mac", help="this PC mac address (lowercase-no-separator, like 9c7bef372fef, defaults to auto detect", default=MAC)
parser.add_argument("-a", "--aid", help="this PC app ID (defaults to 'S9')", default=AID)
parser.add_argument("-v", "--verbose", help="print SGS queries and responses", action="store_true")
args = parser.parse_args()

rid = 'X'+args.aid+args.mac

######################## SGS commands interconnecton

querry = {"command": "device_pairing_start", "receiver": rid, "stb": args.stb, "app": "My_App", "name": "My app", "type": "python", "id": "S9", "mac":args.mac}
url = 'http://' + args.ip + '/sgs_noauth'

# 1. start device pairing. With this command STB should show PIN
if args.verbose: print ("-- start req: ", json.dumps(querry))
response_raw = requests.post(url, data=json.dumps(querry))
if args.verbose: print ("-- start resp:", response_raw.text)

# parse response
try:
   response = json.loads(response_raw.text)
   if response["result"] != 1:
      print ("Error,", response_raw.text)
      exit()
except:
   print ("incorrect json", response_raw.text)
   exit ()


# now let the User enter PIN taht should be displayed at TV:
pin = input("Please enter PIN: ")

# 2. finish pairing
# it uses 'device_pairing_complete' with same parameters as start pairing + pin code
querry["command"] = "device_pairing_complete"
querry["pin"] = pin

if args.verbose: print ("-- start req: ", json.dumps(querry))
response_raw = requests.post(url, data=json.dumps(querry))
if args.verbose: print ("-- start resp:", response_raw.text)

# parse response
try:
   response = json.loads(response_raw.text)
   if response["result"] != 1:
      print ("Error,", response_raw.text)
      exit()
except:
   print ("incorrect json", response_raw.text)
   exit ()

print ()
print ("rid: ",   rid)
print ("login: ", response["name"])
print ("passwd:", response["passwd"])

print ()
print ("use in scripts:")
print ("-l {} -p {} -r {} -i {} -s {}".format(response["name"], response["passwd"], rid, args.ip, args.stb))
