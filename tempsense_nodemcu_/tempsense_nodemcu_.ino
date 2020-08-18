#include <ESP8266WiFi.h>
#include "DHT.h" 
#include <UniversalTelegramBot.h>                       
#define DHTTYPE DHT11   // DHT 11
#define BOTtoken "xxxxxxxxxxxxxxxxx"  // your Bot Token (Get from Botfather)
#define dht_dpin 0
String chat_id;
char ssid[] = "Redmixc";              // your network SSID (name)
char password[] = "spaces3235";   // your network key
DHT dht(dht_dpin, DHTTYPE); 
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
const int ledPin = 2;
int ledStatus = 0;

String test_photo_url = "https://img.srgcdn.com/e/w:750/cjh2NWp4S0FiNWxJQVNsQ3JUU28uanBn.jpg"; // can insert any picture URL

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/get_photo") {
      bot.sendPhoto(chat_id, test_photo_url, "Who");
    }

    //-------------
    //add more commands here
    //-------------
    
    if (text == "/getTemp") {
      float t = dht.readTemperature();
      String txt = "Current temp is "+String(t)+ " C";
      ledStatus = 1;
      bot.sendMessage(chat_id,txt,"");
    }

    if (text == "/getHumidity") {
      float h = dht.readHumidity();
      String txt = "Current Humidity is "+String(h)+" %.";
      bot.sendMessage(chat_id, txt, "");
    }

    if (text == "/getTempf") {
        float f=dht.readTemperature(true);
        String txt = "Current temp in fahreneit is " + String(f)+" F";
        bot.sendMessage(chat_id, txt, "");
       
    }
     if (text == "/options") {
      String keyboardJson = "[[\"/getTemp\", \"/getTempf\"],[\"/status\",\"/getHumidity\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Choose from one of the following options", "", keyboardJson, true);
    }
    

    if (text == "/start") {
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
  Serial.begin(115200);
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
  client.setInsecure(); // if yr core cannot handle secure connections

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off

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
