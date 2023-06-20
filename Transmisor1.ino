// Importar las bibliotecas necesarias
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

// Configuración de red para el emisor
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";

// Dirección IP y puerto para la comunicación
const char* host = "192.168.1.100"; // Dirección IP del receptor
const int port = 8080; // Puerto para la comunicación

// Clave de encriptación para codificar y decodificar los mensajes
const char* encryptionKey = "TU_CLAVE_DE_ENCRIPTACION";

// Crear un cliente WiFi
WiFiClient client;

// Función para encriptar un mensaje
String encryptMessage(String message) {
  String encryptedMessage = "";
  int messageLength = message.length();
  int keyLength = strlen(encryptionKey);
  
  for (int i = 0; i < messageLength; i++) {
    encryptedMessage += message[i] ^ encryptionKey[i % keyLength];
  }
  
  return encryptedMessage;
}

// Función para enviar un mensaje encriptado
void sendMessage(String message) {
  String encryptedMessage = encryptMessage(message);
  
  // Conectarse al servidor
  if (!client.connect(host, port)) {
    Serial.println("No se pudo conectar al servidor");
    return;
  }
  
  // Enviar el mensaje encriptado
  client.println(encryptedMessage);
  
  // Esperar una respuesta
  while (!client.available()) {
    delay(1);
  }
  
  // Leer la respuesta
  String response = client.readString();
  
  // Imprimir la respuesta
  Serial.println(response);
  
  // Cerrar la conexión
  client.stop();
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
  
  // Crear un nuevo mensaje
  String message = "Hola, receptor!";
  
  // Enviar el mensaje encriptado
  sendMessage(message);
}

void loop() {
  // No se realiza ninguna acción adicional en el bucle principal
}
