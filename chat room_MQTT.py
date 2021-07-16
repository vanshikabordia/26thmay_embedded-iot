import paho.mqtt.client as mqtt
import time

def on_connect(client,userdata,flags,rc):
    if(rc==0):  #rc=0 marks a connection successful of the client with the broker
        client.connect_flag = True  #set flag
        print("connected ok")
    else:
        print("Not connected returned code=",rc)

def on_message(client,userdata,message):
    print("message topic",message.topic)
    if(str(message.topic)!=pubtop):
        print(str(message.topic),str(message.payload.decode('utf-8')))

def on_subscribe(client,userdata,mid,granted_qos):
    print("subscribe",str(mid),str(granted_qos))

def on_unsubscribe(client,userdata,mid,granted_qos):
    print("un-subscribed",str(mid))

def on_disconnect(client,userdata,rc):
    if(rc!=0):
        print("unexpected disconnection")

broker_addr="test.mosquitto.org"
port=1883

client=mqtt.Client()
client.on_subscribe=on_subscribe
client.on_unsubscribe=on_unsubscribe
client.on_connect=on_connect
client.on_message=on_message
client.connect(broker_addr,port)

pubtop=input("Topic to be published:")
subtop=input("Topic to be subscribed:")

client.loop_start()
client.subscribe(subtop)

time.sleep(5)

    while(1):
    print("\nProvided functions : \n")
    print("Type 'quit' to exit.")
    print("Type 'sub' to subscribe to new topic.")
    print("Type 'unsub' to unsubscribe the topic ",subtop)
    print("Type 'pub' to publish new topic")
    print("Type 'chat' to start conversation with",subtop)
    choice=input("\nEnter your choice : ")
    print("");
    if(choice=="quit"):
        client.disconnect()
        client.loop_stop()
        break
    elif(choice=="sub"):
        new_subtop=input("Enter topic name to be subscribed : ")
        client.subscribe(new_subtop)
        print("Subscribed to",new_subtop)
    elif(choice=="unsub"):
        unsubtop=input("Enter topic name to be unsubscribed : ")
        client.unsubscribe(unsubtop)
        print(unsubtop," is unsubscribed.")
    elif(choice=="pub"):
        pubtop=input("Enter topic name to be published : ")
    elif(choice=="chat"):
        print("Start conversation")
        print("Type 'quit' to exit conversation\n")
        print("Type your message")
        while(1):
            msg=input()
            if(msg=='quit'):
                break
            else:
                client.publish(pubtop,msg)
                print("Message sent to",subtop)
                print("")
    else:
        print("Invalid ")   
