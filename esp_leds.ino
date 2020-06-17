//led_buitlin::

#include<ESP8266WiFi.h>
const char* ssid="INFINITUM215D_2.4";
const char* password="9212829417";

WiFiServer server(80);
static const uint8_t D0=16; 
static const uint8_t D1=5; 
static const uint8_t D2=4; 
static const uint8_t D3=0; 

int amarillo= D1;

void setup() {
   Serial.begin(9600);
   delay(100);

   pinMode(amarillo, OUTPUT);
  digitalWrite(amarillo, LOW);
  
   Serial.print("Contectar a: ");
   Serial.println(ssid); 
   WiFi.begin(ssid,password);

   while(WiFi.status() != WL_CONNECTED){
    delay(600);
    Serial.print(" .");
    }
    Serial.println("CONECTADO!!");

    server.begin();
    Serial.println("Servidor iniciado en 80");

    // direccion ip::
    Serial.print("direccion: ");
    Serial.print("http://");
    Serial.println(WiFi.localIP());
    
}

void loop() {

 WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }  

    // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/Prende") != -1)  {
    digitalWrite(amarillo, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/Apaga") != -1)  {
    digitalWrite(amarillo, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/Prende\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Apaga\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
