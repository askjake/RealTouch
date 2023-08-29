#!/usr/bin/env python3

# UDP search nearest Dish devices

import sys
import socket
import requests
import time
#import xml.etree.ElementTree as et
import xmltodict
import json

#LOCATION: http://10.79.97.14:49314/device.xml
KEY="LOCATION: "

SSDP_ADDR = "239.255.255.250";
SSDP_PORT = 1900;
SSDP_MX = 5;
SSDP_ST = "urn:schemas-echostar-com:service:EchostarService:1";

#LOCATION="http://10.79.97.14:49314/device.xml"

while True:
   print ("-------------------------------------------------------")
   if 'LOCATION' not in globals():
      ssdpRequest = "M-SEARCH * HTTP/1.1\r\n" + \
                    "HOST: {}:{}\r\n".format(SSDP_ADDR, SSDP_PORT) + \
                    "MAN: \"ssdp:discover\"\r\n" + \
                    "MX: {}\r\n".format(SSDP_MX, ) + \
                    "ST: {}\r\n".format(SSDP_ST, ) + "\r\n";
      data_bytes = bytearray(ssdpRequest, 'utf-8')

      sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      sock.sendto(data_bytes, (SSDP_ADDR, SSDP_PORT))
      data=sock.recv(2000)

      lines = data.decode("utf-8").split("\r\n")
      #print (lines)

      #print ("-----------")
      #for l in lines:
      #   print (l)

      #print ("-----------")
      location = [x[len(KEY):] for x in lines if x.startswith(KEY)][0]
      print ("location:", location)
   else:
      location = LOCATION

   #print ("-----------")
   stb_info = xmltodict.parse(requests.get(location).content)
   #print (json.dumps(stb_info, indent=2))
   print ("RID: {}, ip: {:15} name {}".format(
      stb_info["root"]["device"]["serialNumber"],
      location[len("http://"):-len("/device.xml")],
      stb_info["root"]["device"]["modelName"]))

   print ()

   time.sleep (1)


