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
- Used BotFather for getting bot token
- Imported all the things required and saved token in .env file
``` js
const TelegramBot = require('node-telegram-bot-api'); // using node-telegram-bot-api library
const fetch = require('node-fetch');  
const token = process.env.TOKEN; // Telegram token recieved from BotFather
const request = require('request');
var json;
let settings = { method: "Get" };
// Created instance of TelegramBot 
const bot = new TelegramBot(token, {
    polling: true
});
```
- Do something based on command recieved and send text to the user
``` js
bot.onText(/\/getTempf/,(msg,match) => {
  const chatId = msg.chat.id;
  let url = "http://192.168.43.181/temp.json"; // getting values in json format from the temp.json end
  let options = {json: true};
  request(url, options, (error, res, body) => {
    if (error) {
        return  console.log(error)
    };

    if (!error && res.statusCode == 200) {
        // do something with JSON, using the 'body' variable
        json = res.body;
        JSON.stringify(json); // converting in string format
        console.log(res.body);
    };
    var msg = "Current temperature in fahreneit is "
    msg+= JSON.parse(json.tempF); //parsing the json output recieved
    msg+= "F."
    bot.sendMessage(chatId,msg); //send message
  });
});
```
### Props!
- ArduinoJson
- node-telegram-bot-api
- DHT Library
- ESP Webserver
- ESP Wifi

### Learn about hosting telegram bot ###
[Different libraries than the one I am using but inital steps for creating bot in Telegram app are useful!](https://dev.to/ajaykumbhare/build-a-telegram-bot-using-node-js-171h)
