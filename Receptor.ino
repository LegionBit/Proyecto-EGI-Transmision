#include <ESP8266WiFi.h>

const char* ssid = "TU_SSID";                // Nombre de la red WiFi
const char* password = "TU_CLAVE_WIFI";      // Contraseña de la red WiFi
const int port = 8888;                       // Puerto para la comunicación

WiFiServer server(port);                      // Objeto para gestionar el servidor
WiFiClient client;                            // Objeto para representar al cliente

void setup() {
  Serial.begin(115200);                       // Iniciar la comunicación serial
  WiFi.begin(ssid, password);                 // Conectar al WiFi

  while (WiFi.status() != WL_CONNECTED) {     // Esperar a que se establezca la conexión WiFi
    delay(1000);
    Serial.println("Conectando al WiFi...");
  }

  server.begin();                             // Iniciar el servidor
  Serial.println("Servidor iniciado");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());              // Mostrar la dirección IP asignada al módulo ESP8266
}

void loop() {
  client = server.available();                // Verificar si hay un cliente conectado al servidor

  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      if (client.available()) {
        String encodedMessage = client.readStringUntil('\n');   // Leer el mensaje enviado por el cliente

        String decodedMessage = decodeMessage(encodedMessage);  // Decodificar el mensaje utilizando la función decodeMessage

        Serial.print("Mensaje recibido: ");
        Serial.println(decodedMessage);                         // Mostrar el mensaje decodificado en el monitor serial

        client.stop();                                          // Cerrar la conexión con el cliente
      }
    }
  }
}

String decodeMessage(String encodedMessage) {
  String decodedMessage = "";
  char key = 'K';                            // Clave para el cifrado XOR

  for (int i = 0; i < encodedMessage.length(); i++) {
    decodedMessage += char(encodedMessage[i] ^ key);   // Realizar un cifrado XOR del mensaje recibido con la clave
  }

  return decodedMessage;
}
