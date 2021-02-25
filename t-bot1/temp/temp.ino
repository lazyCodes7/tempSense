// Library Imports //
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>
// Library Imports //

// Variables //
# define PIN 4
# define TYPE DHT11  
DHT dht(PIN, TYPE);  
/*Put your SSID & Password*/
const char* ssid = "Murdock";  // Enter SSID here
const char* password = "Kilgrave";  //Enter Password here
float humidity;                            // variables for humidity, temperature in Celsius and Fahreneit
float tempC;
float tempF;
int rainAnalogVal = 0;                     // collecting values for raining in analog
int isRaining = 0;                         
ESP8266WebServer server(80);  // creating ESP8266 server listening at port 80

// Setup Function //
void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();                           // starting the dht11 sensor

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
  Serial.println("WiFi connected..!");      // wifi success and the ip recieved is printed
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);             
  server.on("/temp.json",outputJson);      // temp.json is the route where sensor values are posted
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

// loop function repeated everytime
void loop() {
  server.handleClient();                    
  humidity = dht.readHumidity();  //humidity
  tempC = dht.readTemperature(); // in Celsius 
  tempF = dht.readTemperature(true);  //in fahreneit
  
}

void handle_OnConnect() {
  server.send(200, "text/html", "Webserver is working");      // Webserver success and works properly
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");               // Function to handle error in connecting
}

// function for creating a buffer that has sensor values
String createJsonResponse() {
  // Buffer is created in which sensor values are stored.
  StaticJsonBuffer<500> jsonBuffer;
  
  JsonObject &root = jsonBuffer.createObject();
  JsonArray &humiValues = root.createNestedArray("humidity");
  humiValues.add(humidity); // adding humidity values
  JsonArray &tempFValues = root.createNestedArray("tempF");
  tempFValues.add(tempF); // adding temperature values 
  JsonArray &tempCValues = root.createNestedArray("tempC");
  tempCValues.add(tempC); // adding temperature values in Celsius
  JsonArray &isRaining = root.createNestedArray("isRaining");
  isRaining.add(isRaining);     // adding rain values
  String json;                
  root.prettyPrintTo(json);     // converting to readable format
  return json;
}

void outputJson() {
    server.send(200, "text/json", createJsonResponse()); // preparing a json response consisting of sensor values
}
