### Approach 2 (Slower) ###
In this approach everything from collecting sensor values and responding to user-texts is handled in one file. It was my inital approach when working on this project but response time was around 10-15 secs hence the 1st approach
- Establishing a connection
``` C++
void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setInsecure(); // if core cannot handle secure connections

 

}
```
- Handling new messages
``` C++
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
}
``` 
- Responding to user texts
``` C++
if (text == "/getTemp") {
      // sending the temp in C
      float t = dht.readTemperature();
      String txt = "Current temp is "+String(t)+ " C";
      ledStatus = 1;
      bot.sendMessage(chat_id,txt,""); //send message 
      
}
```
- Collecting sensor values
``` C++
float t = dht.readTemperature();
float h = dht.readHumidity();
float f=dht.readTemperature(true);
```
### Extras ###
- ESP Wifi
- UniversalTelegramBot
- DHT

### Learn more about UniversalTelegramBot and it's functions here ###
[Checkout README for the functions](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
