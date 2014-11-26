#!/usr/bin/python

import subprocess
import re
import sys
import time
import datetime
import gspread

# ===========================================================================
# Google Account Details
# ===========================================================================

# Account details for google docs
email       = 'slaenner@gmail.com'
password    = ''
spreadsheet = 'Greenhouse Log Data'

# ===========================================================================
# Example Code
# ===========================================================================


# Login with your Google account
try:
  gc = gspread.login(email, password)
except:
  print "Unable to log in.  Check your email address/password"
  sys.exit()

# Open a worksheet from your spreadsheet using the filename
try:
  worksheet = gc.open(spreadsheet).sheet1
  # Alternatively, open a spreadsheet using the spreadsheet's key
  # worksheet = gc.open_by_key('0AualitP_cW3idGdCRTZJM2JCRDZwNEtMWXFfVVNGWlE')
except:
  print "Unable to open the spreadsheet.  Check your filename: %s" % spreadsheet
  sys.exit()

# Continuously append data
while(True):
  
  # Run the DHT program to get the humidity and temperature readings!
  output = subprocess.check_output(["/home/pi/raspigreen_copy/bin/dht11", "Sensor1"]);
  print output
  matches = re.search("Temp:\s+([0-9.]+)C.*", output)
  if (not matches):
	time.sleep(3)
	continue
  temp = float(matches.group(1))
  
  # search for humidity printout
  matches = re.search("RH:\s+([0-9.]+),.*", output)
  if (not matches):
	time.sleep(3)
	continue
  humidity = float(matches.group(1))

  print "Temperature: %.1f C" % temp
  print "Humidity:    %.1f %%" % humidity
  print "Writing to LCD"
  lcd_temp = "Temp: %.1f C" % temp
  lcd_hum = "R.H: %.1f %%" % humidity
  output = subprocess.check_output(["/home/pi/raspigreen_copy/bin//lcd", "Temp: %.1f C" % temp]);
  print output;
 
  # Append the data in the spreadsheet, including a timestamp
  try:
    values = [datetime.datetime.now(), temp, humidity]
    worksheet.append_row(values)
  except:
    print "Unable to append data.  Check your connection?"
    sys.exit()

  # Wait 30 seconds before continuing
  print "Wrote a row to %s" % spreadsheet
  time.sleep(60*15)
