import requests
import serial



com=serial.Serial("COM1",9600)

def thingspeak_read():
    URL='https://api.thingspeak.com/channels/1442240/feeds.json?api_key='
    key='1S8DC0HP24R0A28F'
    header='&results=1'
    new_url=URL+key+header
    get_data=requests.get(new_url).json()
    
    data=get_data['channel']['id']
    val=get_data['feeds'][0]['field1']
    print(get_data)
    print(val)
    

    com.write(val.encode('utf-8'))



while(True):
    thingspeak_read()
    
