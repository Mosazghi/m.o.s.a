# # from servo import Servo
# # import network
# # import urequests
# # import time
# # import machine
import json
import requests


# # WiFi
# ssid = 'Weini2.4G'
# password = '20052009'
# url = 'http://46.15.250.200:4000/bestilling'

# intervall = 5 
# forrige_data = ''

# motstand_servo  = Servo(pin=1)
# bryter_servo    = Servo(pin=2)
# led_servo       = Servo(pin=3)




# def connect_to_wifi():
#     sta_if = network.WLAN(network.STA_IF)
#     if not sta_if.isconnected():
#         print('Connecting to WiFi...')
#         sta_if.active(True)
#         sta_if.connect(ssid, password)
#         while not sta_if.isconnected():
#             pass
#     print('Connected to WiFi')
#     print('IP address:', sta_if.ifconfig()[0])


# def getBestillinger():
#     global forrige_data  
#     res = urequests.get(url)
#     if res.status_code == 200:
#         data = res.json()
#         if data != forrige_data:
#             forrige_data = data
#             bestillinger = data["bestillinger"]
#             return bestillinger
#     res.close()
#     return None


# Tre stasjoner; motstand, bryter, led 
# Kan foreløpig prøve med en bestilling om gangen (en av de tre)
def handleBestillinger(bestilling):
    bestilling_dict = json.loads(bestilling)




def main():
    # connect_to_wifi()
    # while True:
    #     dropNr = getDropNr()
    #     if dropNr is not None:
    #         # Hovedkode her: 
    #         print("Dropsted:", dropNr)
    #         LED.value(1)
    #     else:
    #         LED.value(0)
    #     time.sleep(intervall)
    #     print(dropNr)
    req = requests.get('http://localhost:4000/dashboard/bestilling').json()
    print(req['dropSted'])

if __name__ == '__main__':
    main()
