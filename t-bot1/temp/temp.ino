#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define PIN 4
#define TYPE DHT11  
DHT dht(PIN, TYPE);  
/*Put your SSID & Password*/
const char* ssid = "Murdock";  // Enter SSID here
const char* password = "Kilgrave";  //Enter Password here
float h;
float tempC;
float tempF;
int rainAnalogVal = 0; 
int isRaining = 0;
ESP8266WebServer server(80);
void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();  

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.on("/temp.json",outputJson);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  h = dht.readHumidity();  //humidity
  tempC = dht.readTemperature(); // in Celsius 
  tempF = dht.readTemperature(true);  //in fahreneit
  
}

void handle_OnConnect() {
  server.send(200, "text/html", "Webserver is working"); 
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
String createJsonResponse() {
  StaticJsonBuffer<500> jsonBuffer;
  
  JsonObject &root = jsonBuffer.createObject();
  JsonArray &humiValues = root.createNestedArray("humidity");
  humiValues.add(h);
  JsonArray &tempFValues = root.createNestedArray("tempF");
  tempFValues.add(tempF);
  JsonArray &tempCValues = root.createNestedArray("tempC");
  tempCValues.add(tempC);
  JsonArray &isRaining = root.createNestedArray("isRaining");
  isRaining.add(0);
  String json;
  root.prettyPrintTo(json);
  return json;
}
void outputJson() {
    server.send(200, "text/json", createJsonResponse());
}
