# TOPOLOGÍA DE RED ESTRELLA

# OBJETIVO DE LA PRÁCTICA
Realizar y ejecutar una conexión inalámbrica y un posterior envío de datos a ThingSpeak mediante una placa ESP32 y placas Raspberry Pi Pico W siguiendo los lineamientos de la topología de red estrella. Donde la ESP32 funja como nodo central para el resto de las placas.

# DESCRIPCIÓN
Para esta práctica, elaboramos una demostración de topología de red estrella utilizando placas Raspberry Pi Pico W y ESP32, con el propósito de mandar información a un canal de ThingSpeak a través de la conexión que generan las Raspberry Pi con la ESP32. 

# MATERIAL
Placa ESP32 - Es el nodo central.
Placas Raspberry Pi Pico W - Son los nodos terminales que envían los datos.
Conexión WiFi - Para la comunicación entre dispositivos.
Arduino IDE - Para programar las ESP32.
Thonny IDE - Para programar el Raspberry Pi Pico W.
ThingSpeak - Visualizar y analizar los datos recibidos.

# CÓMO EJECUTAR:
# 1. Abre el código ESP32_Thingspeak.ino en el IDE Arduino. (ESP32)
  Cambia estas variables por tus credenciales:
    const char* ssid = "TU_RED_WIFI";
    const char* password = "TU_CONTRASEÑA";
    const String writeAPIKey = "TU_API_KEY_THINGSPEAK";
    Sube el código al ESP32.
    
  Obtén la IP del ESP32:
    Abre el Serial Monitor (115200 baudios)
    Anota la IP mostrada.

# 2. Abre el código #2 en Thonny IDE. (RASPBERRY)
  Modifica estas variables:
    ssid = "TU_RED_WIFI"
    password = "TU_CONTRASEÑA"
    server_ip = "IP_DEL_ESP32" (La del paso anterior)

  Ejecuta el script.
  Prueba el envío de datos:
    La Pico W enviará datos de ejemplo cada 5 segundos.
    Verifica en el shell que no haya errores.

# 3. Crea un canal:
  Ve a ThingSpeak > "Channels" > "New Channel".
  Nombra el canal y define 2 campos:
    field1: Temperatura.
    field2: Humedad.
  Guarda y copia tu Write API Key (úsala en el código del ESP32).

  Visualiza los datos:
    Entra a "Private View" de tu canal.
    Aquí verás los datos enviados por el ESP32.
