#include <WiFi.h>
#include <WiFiClient.h>

// Configuración Wi-Fi
const char* ssid = "TP-Link_6A4A";  // Tu red Wi-Fi
const char* password = "59574019";  // Tu contraseña Wi-Fi

// Configuración de ThingSpeak
const char* host = "api.thingspeak.com";
const String writeAPIKey = "MGG2RV7J7Z8MVB27";

// Puerto en el que escuchará el servidor
const int port = 80;

WiFiServer server(port);

// Variables para los datos de entrada
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  Serial.begin(115200);

  // Conexión a Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a Wi-Fi...");
  }
  Serial.println("Conexión Wi-Fi establecida");

  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor iniciado en el puerto 80");
}

void loop() {
  // Esperar por nuevos clientes
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Nuevo cliente conectado");

    // Esperar hasta que el cliente envíe datos
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n') {
          // Fin de la solicitud HTTP
          break;
        }
      }
    }

    // Imprimir la solicitud en el monitor serie
    Serial.println("Solicitud recibida: ");
    Serial.println(request);

    // Si se recibe una solicitud HTTP GET
    if (request.indexOf("GET /") != -1) {
      // Leer los datos del formulario enviados
      if (request.indexOf("temperature=") != -1 && request.indexOf("humidity=") != -1) {
        // Parsear los datos de la URL
        int tempIndex = request.indexOf("temperature=") + 12;
        int humIndex = request.indexOf("humidity=") + 9;

        String tempStr = request.substring(tempIndex, request.indexOf("&", tempIndex));
        String humStr = request.substring(humIndex, request.indexOf(" ", humIndex));

        temperature = tempStr.toFloat();
        humidity = humStr.toFloat();

        // Enviar los datos a ThingSpeak
        sendDataToThingSpeak(temperature, humidity);
      }

      // Enviar respuesta HTML con formulario
      String response = "HTTP/1.1 200 OK\r\n";
      response += "Content-Type: text/html\r\n";
      response += "Connection: close\r\n\r\n";
      response += "<html><body><h1>Datos recibidos y enviados a ThingSpeak</h1>";
      response += "Temperatura: " + String(temperature) + "<br>";
      response += "Humedad: " + String(humidity) + "<br>";
      response += "</body></html>";

      // Enviar la respuesta al cliente
      client.print(response);
    }

    // Esperar unos segundos antes de cerrar la conexión
    delay(1);
    client.stop();
    Serial.println("Cliente desconectado");
  }
}

void sendDataToThingSpeak(float temperature, float humidity) {
  WiFiClient client;
  
  // Conectar al servidor de ThingSpeak
  if (client.connect(host, 80)) {
    // Enviar datos a ThingSpeak usando la API
    String url = "/update?api_key=" + writeAPIKey;
    url += "&field1=" + String(temperature); // Datos de temperatura en field1
    url += "&field2=" + String(humidity);    // Datos de humedad en field2
    
    // Enviar la solicitud GET a ThingSpeak
    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(host) + "\r\n");
    client.print("Connection: close\r\n\r\n");
    
    // Esperar la respuesta del servidor
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Timeout al intentar conectar con ThingSpeak");
        client.stop();
        return;
      }
    }

    // Leer la respuesta (opcional)
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }

    // Detener la conexión
    client.stop();
    Serial.println("Datos enviados a ThingSpeak");
  } else {
    Serial.println("Error al conectar a ThingSpeak");
  }
}