import network
import urequests
import time
import machine

ssid = 'Weini2.4G'
password = '20052009'
url = 'http://10.0.0.13:4000/koordinater'
intervall = 5 
LED = machine.Pin(2, machine.Pin.OUT)
forrige_data = ''

def connect_to_wifi():
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.isconnected():
        print('Connecting to WiFi...')
        sta_if.active(True)
        sta_if.connect(ssid, password)
        while not sta_if.isconnected():
            pass
    print('Connected to WiFi')
    print('IP address:', sta_if.ifconfig()[0])

def getDropNr():
    global forrige_data  
    res = urequests.get(url)
    if res.status_code == 200:
        data = res.json()
        if data != forrige_data:
            print('Received new value:', data)
            forrige_data = data
            dropNr = data["drop"]
            return dropNr
    res.close()
    return None

def main():
    connect_to_wifi()
    while True:
        dropNr = getDropNr()
        if dropNr is not None:
            # Hovedkode her: 
            print("Dropsted:", dropNr)
            LED.value(1)
        else:
            LED.value(0)
        time.sleep(intervall)
        print(dropNr)

if __name__ == '__main__':
    main()


