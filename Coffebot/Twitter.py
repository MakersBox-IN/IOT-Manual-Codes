#******************************************#
# Tweet-a-Pot by Gregg Horton 2011 #
# Please email changes or #
# updates to greggahorton@gmail.com #
# *****************************************#

##Import Libraries

import twitter
import serial
import time

##authenticate yourself with twitter
api = twitter.Api(consumer_key='consumerkeyhere', consumer_secret='consumersecrethere', access_token_key='accesskey', access_token_secret='accesssecret')

##set to your serial port
ser = serial.Serial('/dev/ttyUSB0', 19200)

## check serial port
def checkokay():
ser.flushInput()
time.sleep(3)
line=ser.readline()
time.sleep(3)

if line == ' ':
line=ser.readline()
print 'here'
## Welcome message
print 'Welcome To Drip Twit!'
print 'Making Coffee..'
def driptwit():
status = [ ]
x = 0

status = api.GetUserTimeline('X') ##grab latest statuses

checkIt = [s.text for s in status] ##put status in an array

drip = checkIt[0].split() ##split first tweet into words

## check for match and write to serial if match
if drip[0] == '#driptwit':
print 'Tweet Recieved, Making Coffee'
ser.write('1')
elif drip[0] == '#driptwitstop': ##break if done
ser.write('0')
print 'stopped, awaiting instructions.'
else:
ser.write('0')
print 'Awaiting Tweet'

while 1:
driptwit() ## call driptwit function
time.sleep(15) ## sleep for 15 seconds to avoid rate limiting
