#!/usr/bin/env python3
#
# get STB information
#

from sgs_lib import *
import argparse


# get params
parser = sgs_arg_parse(description="get STB information")
parser.add_argument("id", nargs='?', default=6, type=int, choices=range(1,12),
      help =
 '''
 data group id (defaults to 6)
 ID values:
  - 1 ptat_authorized_local_services
  - 2 backup_date
  - 3 smartcard_callout_date
  - 4 contact_information
  - 5 receiver_smartcard
  - 6 system_information (default)
  - 7 sling_information
  - 8 sys_sw_information
  - 9 preference_res
  - 10 hdd_diagnostics
  - 11 mmc_nand_wear_status
 ''')
args = parser.parse_args()

stb = STB(args)

data = stb.sgs_command({"command":"get_stb_information","id":args.id})

if not data:
   print ("error")
   quit()

result = data['result']
if result != 1:
  if "reason" in data.keys():  print ("Error, \"" + data['reason'] + "\" result=" + str(result))
  else:                        print ("Error, result =", str(result))
  quit()

if 6 == args.id and not stb.verbose:
  print ("rxid         ", data["data"]["rxid"])
  print ("smartcard_id ", data["data"]["smartcard_id"])
  print ("hwid         ", data["data"]["hwid"])
  print ("model        ", data["data"]["model"])
  print ("sw_ver       ", data["data"]["sw_ver"])
else:
  print (json.dumps(data, indent=2, separators=("","\t")))
