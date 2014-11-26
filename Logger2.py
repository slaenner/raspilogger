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
spreadsheetName = 'RaspiGreenLog'

# ===========================================================================
# Example Code
# ===========================================================================

class Queue:
  def __init__(self):
    self.items = []
  
  def isEmpty(self):
    return self.items == []
  
  def enqueue(self, item):
    self.items.insert(0,item)
  
  def dequeue(self):
    return self.items.pop()
  
  def size(self):
    return len(self.items)

queueTime = Queue()
queueTemperatur = Queue()
queueHumidity = Queue()


def pushQueue ():
  print ("\npushQueue")
  #read sensor
  sensorReadResult = False;
  while (sensorReadResult == False):
    output = subprocess.check_output(["/home/pi/raspigreen_copy/bin/dht11", "Sensor1"]);
    matches = re.search("Temp:\s+([0-9.]+)C.*", output)
    if (matches):
      temp = float(matches.group(1))
      matches = re.search("RH:\s+([0-9.]+),.*", output)
      if (matches):
        sensorReadResult = True
        humidity = float(matches.group(1))
        dateTimeStamp = datetime.datetime.now()
        #dateTimeStampString = dateTimeStamp.strftime("%Y-%m-%d %H:%M")
        
        print "Push sensor reading into Queue - Queue element: %d; Date/time: %s; Temp: %.1f C; Hum: %.1f %%\n" % (queueTime.size(), dateTimeStamp.strftime("%Y-%m-%d %H:%M"), temp, humidity)

        # Write text to the LCD
        print "Temperature: %.1f C" % temp
        print "Humidity:    %.1f %%" % humidity
        print "Writing to LCD"
        lcd_temp = "Temp: %.1f C" % temp
        lcd_hum = "R.H: %.1f %%" % humidity
        output = subprocess.check_output(["/home/pi/raspigreen_copy/bin//lcd", "Temp: %.1f C :-)" % temp]);

        #push the reading into the queue
        queueTime.enqueue (dateTimeStamp)
        queueTemperatur.enqueue (temp)
        queueHumidity.enqueue (humidity)
      else:
        time.sleep(3)

def popQueue ():
  print ("\npopQueue")
  if (queueTime.size() != 0):
    try:
      gc = gspread.login(email, password)
      spreadsheet = gc.open(spreadsheetName)
      worksheet = spreadsheet.get_worksheet(7)
      dateTimeStamp = queueTime.dequeue()
      temp = queueTemperatur.dequeue()
      humidity = queueHumidity.dequeue()
      print "Pop sensor reading from Queue - Queue element: %d; Date/time: %s; Temp: %.1f C; Hum: %.1f %%\n" % (queueTime.size(), dateTimeStamp.strftime("%Y-%m-%d %H:%M"), temp, humidity)
      worksheet.update_cell (2,1,dateTimeStamp);
      worksheet.update_cell (2,2,temp);
      worksheet.update_cell (2,3,humidity);
    
    except:
      print "Unable to access spreadsheet"
  #subprocess.call(["ifup", "--force", "wlan0"])
  #subprocess.check_output(["ifup --force wlan0"]);
  
  else:
    print "no elements in queue"

def main ():
  counter = 0;
  while (True):
    if (counter == 0):
      pushQueue ()
    popQueue()
    counter += 1
    # Queue Pop every 30 sec; Sensor ready every 30*28 = 14 min
    counter %=28
    time.sleep(30)

main()
