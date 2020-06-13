#include <DHT.h>
#define PIN 2
#define TYPE DHT11  
// Prototype Declartion  
unsigned long int milli_time;
DHT dht(PIN, TYPE);  
void setup() {  
    Serial.begin(9600);  
    Serial.println("CLEARDATA");//clears data everytime we connect to plx-daq
    //Start  
    dht.begin();  
  Serial.println("LABEL,Time,Temperature(c),Humidity,Temperature(f)");  //Label creates columns with bold font
                                      
}  
void loop() {  
    float humidity = dht.readHumidity();  //humidity
    float temp_cel = dht.readTemperature(); // in Celsius 
    float temp_farh = dht.readTemperature(true);  //in fahreneit
    if (isnan(humidity) || isnan(temp_cel) || isnan(temp_farh)) {  //if the program fails it would give nan values which means either sensor is broken or connection is incorrect
        //isnan = is NOT A NUMBER which return true when it is not a number  
        Serial.println("# Sorry, Failed to Read Data From DHT Module");  
        return;  
    } else {  
        // For Humidity  
        Serial.print("DATA,TIME,");  
        Serial.print(temp_cel);  
        // For Temprature   
        Serial.print(",");  
        Serial.print(humidity);  
        Serial.print(",");  
        Serial.println(temp_farh);   
        delay(2000);
    }  
}  
