// Importar las bibliotecas necesarias
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

// Configuración de red para el receptor
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Dirección IP y puerto para la comunicación
const int port = 8080; // Puerto para la comunicación

// Clave de encriptación para codificar y decodificar los mensajes
const char* encryptionKey = "TU_CLAVE_DE_ENCRIPTACION";

// Crear un servidor WiFi
WiFiServer server(port);
WiFiClient client;

// Función para desencriptar un mensaje
String decryptMessage(String encryptedMessage) {
  String decryptedMessage = "";
  int messageLength = encryptedMessage.length();
  int keyLength = strlen(encryptionKey);
  
  for (int i = 0; i < messageLength; i++) {
    decryptedMessage += encryptedMessage[i] ^ encryptionKey[i % keyLength];
  }
  
  return decryptedMessage;
}

// Función para recibir un mensaje y desencriptarlo
String receiveMessage() {
  // Esperar a que se establezca una conexión con el cliente
  while (!client.available()) {
    WiFiClient client = server.available();
  }
  
  // Leer el mensaje encriptado
  String encryptedMessage = client.readStringUntil('\n');
  
  // Desencriptar el mensaje
  String message = decryptMessage(encryptedMessage);
  
  // Devolver el mensaje desencriptado
  return message;
}

void setup() {
  // Inicializar el puerto serial
  Serial.begin(115200);
  
  // Conectarse a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Imprimir la dirección IP
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  
  // Iniciar el servidor
  server.begin();
}

void loop() {
  // Esperar a que se establezca una conexión con el cliente
  while (!client.available()) {
    WiFiClient client = server.available();
  }
  
  // Recibir el mensaje desencriptado
  String message = receiveMessage();
  
  // Imprimir el mensaje recibido
  Serial.println("Mensaje recibido: " + message);
  
  // Enviar una respuesta al cliente
  client.println("Mensaje recibido correctamente");
  client.stop();
}
