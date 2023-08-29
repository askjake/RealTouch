#!/usr/bin/env python3
#
# send remote keys
#
# Usage for help:
#  ./sgs_remote.py -h
#
# Example
#  ./sgs_remote.py -l v0001_client_4ce2e5e53f58a15edc9b5b52895b03c4e831eb9f -p 55b145de6710b27b3bab7900dbcf3f64e36b03b3 -r XS99c7bef372fef -i 192.168.1.115 -s R1911703199-05 Cancel
#

from time import sleep
import sys
import argparse
import os
import json
import requests
from requests.auth import HTTPDigestAuth

# to remove warnings export the following bash env
# export PYTHONWARNINGS="ignore:Unverified HTTPS request"

SUPPORTED_KEYS = [
      "Power Toggle",
      "Power On",
      "Power Off (Not supported)",
      "Enter",
      "Cancel",
      "Guide",
      "Menu",
      "DVR",
      "Search",
      "Keypad",
      "Pause/Play",
      "Rewind",
      "Fast Forward",
      "Stop",
      "Skip Back",
      "Step Forward",
      "Format",
      "System Wizard",
      "Input",
      "Recover",
      "0","1","2","3","4","5","6","7","8","9","*","#",
      "Page Down",
      "Page Up",
      "Pause",
      "Play",
      "Record",
      "Blue",
      "Green",
      "Red",
      "Yellow",
      "Left",
      "Right",
      "Up",
      "Down",
      "Info",
      "Live TV",
      "Jump",
      "Recall",
      "PiP Toggle",
      "PiP Position",
      "PiP Swap",
      "DISH",
      "Sys Info",
      "Mode",
      "Mute",
      "Volume Down",
      "Volume Up"
      ]



############## STB class
class Stb (object):
   def __init__ (self, ip=None, rid=None, stb=None,
         login=None, passwd=None, verbose=False):
      self.ip = ip
      self.rid = rid
      self.stb = stb
      self.login = login
      self.passwd = passwd
      self.verbose = verbose

   def sgs_query(self, data):
      headers = {'content-type': 'application/json'}
      url = 'https://' + self.ip + '/www/sgs'
      if self.verbose: print ()
      if self.verbose: print ("  --- request:  ",json.dumps(data))
      # determine the relative path from this file to the crt & key files
      relative_path = os.path.dirname(os.path.abspath(__file__))
      relative_path += os.path.sep

      response = requests.post(url, auth=HTTPDigestAuth(self.login, self.passwd),
                               data=json.dumps(data),
                               verify=False,
                               cert=(relative_path + "cert.pem", relative_path + "key.pem"),
                               headers=headers)
      try:
         result = json.loads(response.text)
         if self.verbose: print ("  --- responce: ", response.text)
      except:
         self.logger.error("\n\n INCORRECT JSON RESPONSE \n\n")
         result = {'result' : -3}
      return result

# get params
parser = argparse.ArgumentParser(description="send IR keys over SGS",
      epilog =
      '''
Example:
./sgs_remote.py -l v0001_client_4ce2e5e53f58a15edc9b5b52895b03c4e831eb9f -p 55b145de6710b27b3bab7900dbcf3f64e36b03b3 -r XS99c7bef372fef -i 192.168.1.115 -s R1911703199-05 Cancel

Note, the Python may print warnings about non-registered certificate.
to remove warnings export the following bash env
export PYTHONWARNINGS="ignore:Unverified HTTPS request"
      ''',
                                 formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("keys", help="list of keypresses to send to STB", nargs='+')
parser.add_argument("-i", "--ip",      help="specify STB IP", required=True)
parser.add_argument("-s", "--stb",     help="specify STB receiver ID", required=True)
parser.add_argument("-r", "--rid",     help="specify this PC RID (format 'XC9<mac-addr-lowercase-no-separator' like XS99c7bef372ff0)", required=True)
parser.add_argument("-l", "--login",   help="logit to use for HTTPDigestAuth", required=True)
parser.add_argument("-p", "--passwd",  help="logit to use for HTTPDigestAuth", required=True)
parser.add_argument("-t", "--time",    help="time delay in ms between key-presses", default=200)
parser.add_argument("-v", "--verbose", help="print SGS queries and responces", action="store_true")
parser.add_argument("-L", "--list",    help="list supported keys", action="store_true")
args = parser.parse_args()

stb = Stb(
      ip = args.ip,
      stb = args.stb,
      rid = args.rid,
      login = args.login,
      passwd = args.passwd,
      verbose = args.verbose
      )


if args.list:
   print ("supported keys: \n", SUPPORTED_KEYS)
   exit()

DELAY = args.time


######################## SGS commands interconnecton

# suppose this PC is already paired, so we know the login and password, and hopper knows our "receiver" value ('rid')

# 1. Attach
response = stb.sgs_query({"command": "attach", "receiver": stb.rid, "stb": stb.stb, "tv_id": 0, "attr": 1})
if response and response["result"] == 1:
   stb.cid = response["cid"]
else:
   if "result" in response.keys(): print("Error, attach failed with result", response["result"])
   else: print("attach failed with no responce")
   exit()

# 2. go on main loop sending keys
for key in args.keys:
   response = stb.sgs_query({"command":"remote_key","stb":stb.stb,"tv_id":"0","key_name": key, "receiver":stb.rid, "cid":stb.cid})
   if not (response and response["result"] == 1):
      if "reason" in responce.keys() and "result" in responce.keys(): print ("Error, sending {} key: result {}, reason {}".format(key, response["reason"], str(result)))
      else: print ("Error, sending {} key: {}".format(key, json.dumps(responce)))
      exit()
   sleep(DELAY/1000)

# 3. Detach
response = stb.sgs_query({"command": "detach", "receiver": stb.rid, "cid": stb.cid})
if not (response and response["result"] == 1):
   print ("Error, detach fail", json.dumps(responce)) 
