from time import sleep
import sys
import os
import json
import requests
from uuid import getnode as get_mac

# default values
MAC = ''.join(['{:02x}'.format((get_mac() >> i) & 0xff) for i in range(0, 8*6, 8)][::-1])
AID = 'S9'

def start_pairing(stb, ip, mac=None, aid='S9', verbose=False):
    if mac is None:
        mac = ''.join(['{:02x}'.format((get_mac() >> i) & 0xff) for i in range(0, 8*6, 8)][::-1])
    rid = 'X'+aid+mac
    query = {"command": "device_pairing_start", "receiver": rid, "stb": stb, "app": "Jakes JAM", "name": "Jakes JAM", "type": "python", "id": "S9", "mac":mac}
    url = 'http://' + ip + '/sgs_noauth'
    if verbose: 
        print ("-- start req: ", json.dumps(query))
    response_raw = requests.post(url, data=json.dumps(query))
    if verbose: 
        print ("-- start resp:", response_raw.text)
    response = json.loads(response_raw.text)
    return response

def finish_pairing(stb, ip, pin, mac=None, aid='S9', verbose=False):

    if mac is None:
        mac = ''.join(['{:02x}'.format((get_mac() >> i) & 0xff) for i in range(0, 8*6, 8)][::-1])
    rid = 'X'+aid+mac
    query = {"command": "device_pairing_complete", "receiver": rid, "stb": stb, "app": "Jakes JAM", "name": "Jakes JAM", "type": "python", "id": "S9", "mac":mac, "pin": pin}
    url = 'http://' + ip + '/sgs_noauth'
    if verbose: 
        print ("-- start req: ", json.dumps(query))
    response_raw = requests.post(url, data=json.dumps(query))
    if verbose: 
        print ("-- start resp:", response_raw.text)
    response = json.loads(response_raw.text)
    return response