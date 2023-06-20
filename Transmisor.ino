#include <ESP8266WiFi.h>

const char* ssid = "TU_SSID";
const char* password = "TU_CLAVE_WIFI";
const char* ipAddress = "192.168.1.100"; // Dirección IP de la placa receptora
const int port = 8888; // Puerto para la comunicación

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando al WiFi..."); // Mensaje para mostrar en el monitor serie mientras se conecta al WiFi
  }

  Serial.println("Conectado al WiFi"); // Mensaje para mostrar en el monitor serie una vez conectado al WiFi
}

void loop() {
  if (!client.connected()) { // Si no está conectado al cliente
    if (client.connect(ipAddress, port)) { // Intenta conectarse al cliente utilizando la dirección IP y el puerto
      Serial.println("Conexión establecida"); // Mensaje para mostrar en el monitor serie cuando se establece la conexión

      // Mensaje a enviar
      String message = "Hola, receptor";

      // Codificar el mensaje
      String encodedMessage = encodeMessage(message);

      // Enviar el mensaje codificado
      client.print(encodedMessage); // Envia el mensaje codificado al cliente

      Serial.println("Mensaje enviado"); // Mensaje para mostrar en el monitor serie cuando se envía el mensaje
      client.stop(); // Detiene la conexión con el cliente
    }
  }
  delay(5000); // Espera 5 segundos antes de intentar enviar el siguiente mensaje
}

String encodeMessage(String message) {
  String encodedMessage = "";
  char key = 'K'; // Clave para el cifrado XOR

  for (int i = 0; i < message.length(); i++) {
    encodedMessage += char(message[i] ^ key); // Realiza la operación XOR entre cada carácter del mensaje y la clave y agrega el resultado al mensaje codificado
  }

  return encodedMessage; // Devuelve el mensaje codificado
}
