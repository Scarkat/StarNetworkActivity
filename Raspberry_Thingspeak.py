import network
import time
import urequests

# Configuración Wi-Fi
ssid = "TP-Link_6A4A"  # Tu red Wi-Fi
password = "59574019"  # Tu contraseña Wi-Fi

# IP del servidor ESP32
server_ip = "192.168.1.114"  # Cambia por la IP de tu ESP32

# Conectar la Raspberry Pi Pico W a la red Wi-Fi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    
    if not wlan.isconnected():
        print('Conectando a la red Wi-Fi...')
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            time.sleep(1)
        print('Conexión Wi-Fi establecida')
    else:
        print('Ya está conectado a Wi-Fi')

# Función para enviar datos al servidor ESP32
def send_data_to_esp32(temperature, humidity):
    url = f'http://{server_ip}/?temperature={temperature}&humidity={humidity}'
    try:
        response = urequests.get(url)
        print('Datos enviados:', temperature, humidity)
        print('Respuesta del servidor:', response.text)
        response.close()
    except Exception as e:
        print("Error al enviar datos:", e)

# Conectar a la red Wi-Fi
connect_wifi()

# Enviar datos periódicamente
while True:
    temperature = 25.0  # Temperatura de ejemplo
    humidity = 60.0  # Humedad de ejemplo

    send_data_to_esp32(temperature, humidity)
    
    time.sleep(5)  # Esperar 5 segundos antes de enviar nuevamente