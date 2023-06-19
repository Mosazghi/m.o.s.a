import time
import requests

startTid = time.time()

while True:
    req = requests.get("http://127.0.0.1:3000/koordinater").json()
    x, y = req["x"], req["y"]
    print(x, y)
    
    # Sende GET req  hvert 5. sekund (foreløpig løsning)
    time.sleep(5.0 - ((time.time() - startTid) % 5.0))  
