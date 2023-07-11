# import network
# import urequests
import time
# import machine
import json
import requests
# ssid = 'Weini2.4G'
# password = '20052009'
intervall = 5 
# LED = machine.Pin(2, machine.Pin.OUT)
forrige_data = ''

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

get_url = 'http://10.22.209.38:4000/dashboard/api/bestilling'
patch_url = 'http://10.22.209.38:4000/komponent/api/'

def kjorTilHjem():
    print("Kjører tilbake til ladestasjon...")



def getBestilling():
    global forrige_data  
    res = requests.get(get_url)
    if res.status_code == 200:
        data = res.json()
        if data != forrige_data:
            print('Ny bestilling:', data)
            forrige_data = data
            bruker = data["bruker"]
            dropNr = data["dropSted"]
            komponenter = data["komponenter"]
            return bruker, dropNr, komponenter
    res.close()
    return None, None, None


def handleKomponenter(bestilling):
    print("antall komp til bestilling: ",len(bestilling))

    for komponent in bestilling:
        navn = komponent['Komponent']
        antall = komponent['Antall']
        requests.patch(patch_url + navn, data={'antall': antall})
        # print("komponent: ", komponent)
        if antall: 
            if(navn == 'LED'):
                print(f'Henter {antall}  LEDs... ')
            elif(navn == 'Motstand'):
                print(f'Henter {antall} motstander...')
            elif(navn == 'Bryter'):
                print(f'Henter {antall} brytere... ')

def kjorTilDropSted(dropNr):
    if dropNr == 1:
        print("Kjører til dropsted 1")
    elif dropNr == 2:
        print("Kjører til dropsted 2")
    elif dropNr == 3:
        print("Kjører til dropsted 3")
    elif dropNr == 4:
        print("Kjører til dropsted 4")

def main():
    # connect_to_wifi()
    while True:
        bruker, dropNr, komponenter = getBestilling()
        if bruker != None and dropNr != None and komponenter != None:
            # Hovedkode her: 
            print("------------------")
            print("Bruker:", bruker)
            print("Dropsted:", dropNr)
            print("Komponenter:", komponenter)
            print("------------------")
            handleKomponenter(komponenter)
            time.sleep(3)
            kjorTilDropSted(dropNr)
            time.sleep(3)
            kjorTilHjem()
        else:
            print("Ingen nye bestillinger")
        time.sleep(intervall)

if __name__ == '__main__':
    main()


