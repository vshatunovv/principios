// Open Lanuza Thingspeak Ver 1.3
//
//MEDIDOR DE TEMPERATURA Y HUMEDAD
//Publica datos en Thingspeak
//www.openlanuza.com

#include <ThingSpeak.h> // Include ThingSpeak Library
#include <ESP8266WiFi.h> // Include ESP8266wifi Library

const int MQ_PIN = A0; // Variable del pin de entrada del sensor (A0)
const int sensorPin = 0;

char ssid[] = "AndroidAP"; // Nombre del WiFi (nombre del router)
char pass[] = "123123123"; // WiFi router password
unsigned long myChannelNumber = 868999; // Thingspeak número de canal
const char * myWriteAPIKey = "3YT8XPGM38P7N25Y"; // ThingSpeak write API Key

//Variable a la cual le vamos a pasar lo que midamos
float gasC;
float movM;
//no tocar
int status = WL_IDLE_STATUS;

WiFiClient client;

void setup() {
  Serial.begin (9600);
  
 Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
  
//NO TOCAR
WiFi.begin(ssid, pass); // Inicia WiFi
//WiFi.begin(ssid); // Inicia WiFi
ThingSpeak.begin(client); // Inicia ThingSpeak


Serial.begin(115200); // Velocidad puerto serie

Serial.println();
Serial.print("Conectando a ");
Serial.print(ssid);

while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}

Serial.println();
Serial.println("Conectado a WiFi");
Serial.print("Dirección IP: ");
Serial.println(WiFi.localIP());

}

void loop() {
  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  //tempC = analogRead(pinLM35); 
  //Serial.println(tempC);
  // Calculamos la temperatura con la fórmula
 // tempC = ((5.0 * tempC * 100.0)/1024.0)*8; 
gasC = analogRead(MQ_PIN);
int movM = 0;
movM = digitalRead(sensorPin);
 

Serial.print("Raw: ");
Serial.print(gasC);

if (movM == HIGH) {
      Serial.println("Detectado obstaculo");
}


// Carga los valores a enviar
ThingSpeak.setField(1, gasC);
ThingSpeak.setField(2, movM);
// Escribe todos los campos a la vez.
ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);


// Añadimos un retraso para limtitar el número de escrituras en Thinhspeak

delay(3000);



}
