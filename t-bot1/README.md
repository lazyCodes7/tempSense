## Approach 1 (Faster) ##
### nodeMCU part ###
- Reading sensor values
``` C++
void loop() {
  server.handleClient();                    
  humidity = dht.readHumidity();  //humidity
  tempC = dht.readTemperature(); // in Celsius 
  tempF = dht.readTemperature(true);  //in fahreneit
  
}
```
- Connect to WiFi and setup webserver
``` C++
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
```
- Create Buffer where sensor values are posted to 'temp.json' route
``` C++
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
```
### Telegram part ###
