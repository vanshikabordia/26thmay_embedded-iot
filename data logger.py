import random
import urllib.request
import time

def thingspeak_write():
    val0 = random.randint(1,100)
    URL = 'https://api.thingspeak.com/update?api_key='
    key = 'SEVHEQ6ZUMTZD2EQ'
    header1 = '&field1={}'.format(val0)
    new_url1 = URL+key+header1
    print("Random val0 = ",val0)
    print(new_url1)
    v = urllib.request.urlopen(new_url1)
    print(v)
    print("Send data\n")
    
while(True):
    thingspeak_write()
    time.sleep(20)                    #min =  15 sec delay
