// Imports
# include <ESP8266WiFi.h>
# include "DHT.h" 
# include <UniversalTelegramBot.h>       

// define
# define DHTTYPE DHT11   // DHT 11
# define BOTtoken "your token"  // your Bot Token (Get from Botfather)
# define dht_dpin 2

// variables
String chat_id;
char ssid[] = "Redmixc";              // your network SSID (name)
char password[] = "password";   // your network key
DHT dht(dht_dpin, DHTTYPE); 
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client); // Creating an instance of UniversalTelegramBot


// function for handling new messages that are recieved.
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

   

    // if text is /getTemp
    if (text == "/getTemp") {
      // sending the temp in C
      float t = dht.readTemperature();
      String txt = "Current temp is "+String(t)+ " C";
      ledStatus = 1;
      bot.sendMessage(chat_id,txt,""); //send message 
      
    }

    // if text is /getHumidity
    if (text == "/getHumidity") {
      // sending the humidity
      float h = dht.readHumidity();
      String txt = "Current Humidity is "+String(h)+" %.";
      bot.sendMessage(chat_id, txt, "");
      
    }
    
    // if text is /getTempf
    if (text == "/getTempf") {
        // sending the temp
        float f=dht.readTemperature(true);
        String txt = "Current temp in fahreneit is " + String(f)+" F";
        bot.sendMessage(chat_id, txt, "");
       
    }
    
     // if text is /options
     if (text == "/options") {
      // replying with Reply Keyboard
      String keyboardJson = "[[\"/getTemp\", \"/getTempf\"],[\"/status\",\"/getHumidity\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Choose from one of the following options", "", keyboardJson, true);
       
    }
    
    // if text is /start
    if (text == "/start") {
      // sending a welcome message
      String welcome = "Welcome to tempAssist, " + from_name + ".\n";
      welcome += "You can detect your room's temperature,humidity and it will also send you notifications if it's raining.\n\n";
      welcome += "/getTemp : for getting the temperature value in your room\n";
      welcome += "/getHumidity : for getting humidity values in your room\n";
      welcome += "/getTempf : temperature value in fahreneit\n";
      welcome += "/status : Returns current status of room\n";
      bot.sendMessage(chat_id, welcome, "");
      
    }
  }
}
void setup() {
  Serial.begin(9600);
  dht.begin();
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
void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
