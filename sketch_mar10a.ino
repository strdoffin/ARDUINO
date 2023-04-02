
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//----------------------------------------

#define ON_Board_LED 2 

#define D7 15 //D8
#define D5 14 //D4


const char* ssid = "BIG_2G";
const char* password = "big0817133923";

String host_or_IPv4 = "http://192.168.2.38/";

String Destination = "";
String URL_Server = "";
String getData = "";
String payloadGet = "";

HTTPClient http;
WiFiClient client;
//----------------------------------------

void setup() {
 
  Serial.begin(9600);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

  pinMode(D5,OUTPUT);
  digitalWrite(D5, LOW);
  pinMode(D7,OUTPUT);
  digitalWrite(D7, LOW);

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(2000);
}

void loop() {
  int id = 1; //--> ID in Database 
  getData = "ID=" + String(id);
  Destination = "switch.php/";
  URL_Server = host_or_IPv4 + Destination;
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(URL_Server);
  http.begin(client, URL_Server); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(URL_Server+getData); //--> Send the request
  String payload = http.getString(); //--> Get the response payload from server
  Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
  Serial.println(httpCodeGet); //--> Print HTTP return code
  Serial.print("Returned data from Server : ");
  Serial.println(payload); //--> Print request response payload
  if (payload == "1") {
    digitalWrite(D5, HIGH); //--> Turn on Led
  }
  if (payload == "0") {
    digitalWrite(D5, LOW); //--> Turn off Led
  }
  //----------------------------------------
  
  Serial.println("----------------Closing Connection----------------");
  http.end(); //--> Close connection
  Serial.println();
  Serial.println("Please wait 10 seconds for the next connection.");
  Serial.println();
  delay(2500); //--> GET Data at every 10 seconds. From the tests I did, when I used the 5 second delay, the connection was unstable.
  String getwaterdata = "ID=2";
  String serwater = "http://192.168.2.39/switchwater.php/";
  http.begin(client, serwater);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  httpCodeGet = http.POST(URL_Server+getData);
  String waterpayload = http.getString();
  Serial.print("Returned data from Server : ");
  Serial.println(waterpayload); //--> Print request response payload
  if (waterpayload == "1") {
    digitalWrite(D7, HIGH); //--> Turn on Led
  }
  if (waterpayload == "0") {
    digitalWrite(D7, LOW); //--> Turn off Led
  }
  http.end();
  
}
