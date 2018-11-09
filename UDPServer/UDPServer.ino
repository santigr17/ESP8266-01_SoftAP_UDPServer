/**
 * Instituto Tecnológico de Costa Rica
 * Area acdémica de Ingeniería en Computadores
 * Computer Engineering
 * 
 * Profesor: Milton Villegas Lemus
 * Curso: Taller de programación
 * 
 * Autor: Santiago Gamboa Ramírez
 * Versión IDE: 1.8.7
 * 2018
 * 
 * 
 * 
 */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "CarWiFi";       // Nombre de la Red que se va a crear 

bool newSerial;                     // Indica si se debe responder al cliente, con el mensaje del serial
String inputString;                 // Guarda los datos que son leídos desde el serial.
unsigned char response[1024];       // Espacio para almacenar los bytes de los datos del mensaje de serial

int newMsg;                         // Indica si hay un nuevo mensaje desde el cliente.
char udpMsg[1024];                  // Espacio para guardar el mensaje del cliente
char  autoReply[] = "ok;";          // En caso de no haber datos en el puerto serial se envía "ok;"

WiFiUDP wifiUDP;                    // Crea el objeto de tipo UDP para levantar el servidor
unsigned int localPort = 7070;      // Puerto por el que se reciben los mensajes.

// Configuración de la IP estática
// Los clientes se conectan al local_IP
IPAddress local_IP(192,168,4,7);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200);             // El módulo trabaja con ese BaudRate

  //Se crea y configura el punto de acceso, para que otros dispositivos puedan conectarse 
  Serial.println("Creating an Access Point");
  Serial.print("Settiing soft-AP confuguration .... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Settiing the Access Point .... ");
  Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!" );    
  delay(2000);
  //Se crea el servidor UDP que comienza a escuchar en el puerto especificado.
  Serial.println("Starting UDP server");
  bool CarServer = wifiUDP.begin(localPort);
  if(CarServer)
  {
    Serial.print("Listenning at \nIP: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("local port: ");
    Serial.println(wifiUDP.localPort());
    Serial.println("Waiting for connection....");
    inputString = "";
    newSerial = false;
  }
  else{
    Serial.println("Can Start the Server\n Please Reset the module");
    while (true) {delay(500);}
  }
}

void loop() {
  newMsg = wifiUDP.parsePacket();               // Verificar si existe un nuevo mensaje del cliente
  if (newMsg){                                  
    //Serial.println("New message");            
    int len = wifiUDP.read(udpMsg, 1024);       // read the packet into the buffer, we are reading only one byte
    if(len>0){                                  // Eliminamos caracter de finalización
      udpMsg[len] = 0;
    }
    Serial.println(udpMsg);                     // Se envía el mensaje por el serial al arduino o atmega
    wifiUDP.beginPacket(wifiUDP.remoteIP(), wifiUDP.remotePort()); //Se comienza a escribir la respuesta
    if(newSerial)                               // Si hay un mensaje pendiente del Serial se responde con este mensaje.
    {
      inputString.getBytes(response,1024);      // Convertir string a bytes
      wifiUDP.write("Serial:");                 // Los mensajes provenientes del Serial comienzan con "Serial:"
      wifiUDP.write(response,1024);             // Se escriben los datos
      inputString = "";                         // Se limpia la variable
      newSerial = false;                        // Habilitamos el puerto serial para leer otra vez.
    }
    else{ wifiUDP.write(autoReply); }
    wifiUDP.endPacket();
  }
  serialEvent();
  delay(50);
}

/**
 * Función para leer el serial
 * Serial.available retorna si hay bytes por leer en el puerto serial
 * Si el carctér es ";" termina el mensaje y no lee de nuevo hasta no enviar el mensaje anterior.
 */
void serialEvent(){
  while(Serial.available()>0 && !newSerial)
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar == ';' or inChar == '\n')
    {
      newSerial = true;
      break; 
    }
  }
}
