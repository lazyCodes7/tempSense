# tempSense :umbrella:
## What does it do :ear:
Basically, tempSense is a Telegram Bot that can get us the temperature(in Celsius or Fahreneit),humidity when we ask for it. You can ask this bot whether it's a good time to dry out clothes and it will also send notifications if it starts raining and will caution you to remove clothes if such an event happens. This is my first ever IoT project and I have only started to explore this field and there is a lot more to learn as of now. So this project is simple but useful as well.

### Components Used
<ul>
  <li>NodeMCU</li>
  <li>DHT11 sensor</li>
  <li>Rain sensor</li>
  <li>Jumper Cables</li>
  <li>B-Type USB Cable</li>
</ul>
  
### How was it built?
I tried two approaches for building the bot. 
<ul>
  <li>[!](Using telegram bot libraries for nodeMCU and also collecting the sensor values as well)</li>
  <li>[](Collecting sensor values and posting it to a webserver hosted using nodeMCU and also building a server for telegram using node.js which will get these values from the esp webserver)</li>
</ul>
   
