# tempSense :umbrella:
## What does it do :ear:
Basically, tempSense is a Telegram Bot that can get us the temperature(in Celsius or Fahreneit),humidity when we ask for it. You can ask this bot whether it's a good time to dry out clothes and it will also send notifications if it starts raining and will caution you to remove clothes if such an event happens. This is my first ever IoT project and I have only started to explore this field and there is a lot more to learn as of now. So this project is simple but useful as well.

## Components Used
<ul>
  <li>NodeMCU</li>
  <li>DHT11 sensor</li>
  <li>Rain sensor</li>
  <li>Jumper Cables</li>
  <li>B-Type USB Cable</li>
</ul>
  
## Third Party Libraries:key:
<ul>
  <li><a href="https://github.com/bblanchon/ArduinoJson">Arduino Json</a></li>
  <li><a href="https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot">Universal Telegram Bot</a></li>
 </ul>
 <h2>My Approach to the Project</h2>
 <ul>
  <li>First I made the connections to the NodeMCU and made sure if I am getting sensor values</li>
  <li>Went to Telegram and set up my bot</li>
  <li>Used Universal Telegram Bot library for accessing the Telegram Bot and ran some example sketches</li>
  <li>Through the examples I modified the code for getting temp values if user asks for them</li>
  <li>Wrote function for handling new messages</li>
  <li>Wrote function for checking if it's suitable time for drying clothes</li>
  <li>Used Arduino Json library for Reply Keyboards and learned how to use it for my project through examples given</li>
  </ul>
 <h2>How to Use</h2>
 <ul>
  <li>First connect the NodeMCU to the rain sensor and temperature and humidity sensor(Follow the code for the pins)</li>
  <li>After connecting see if you get temp values in Serial Monitor</li>
  <li>Now got to Telegram and go to BotFather and set up a bot</li>
  <li>Use the bot token in the code given and also change ssid and password with yours</li>
  <li>After all this load the code again on the board and see if your bot is working</li>
  </ul>
  <h2>Approx Cost</h2>
  <ul>
  <li>DHT 11 sensor - 100-200 Rs</li>
  <li>Rain Sensor - 100-200 Rs</li>
  <li>NodeMCU with ESP8266-12E module - 300-400 Rs</li>
  <li>Jumper Cables(bulk)- 100-200 Rs</li>
  <li>USB B-Type Cable - 300-400 Rs(you can use your charging cable as well if you have B-Type Cable</li>
  </ul>
  
<h2>Screenshots</h2>
<img src="https://user-images.githubusercontent.com/53506835/90505384-26194b00-e170-11ea-8c1d-0a05434e9ae7.jpg" width=50%>
