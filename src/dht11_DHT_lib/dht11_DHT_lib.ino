
#include <DHT.h>                                // Including library for dht

#define DHTPIN 2                                // pin where the dht11 is connected (D4 NodeMCU V1)
#define DHTTYPE DHT11                           // defining which DHT sensor type

DHT dht(DHTPIN, DHTTYPE);                       // create dht11 instance 
 
void setup() 
{
       Serial.begin(115200);            
       delay(10);
       dht.begin();
       
}
 
void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
      if (isnan(h) || isnan(t)) 
       {
          Serial.println("Failed to read from DHT sensor!");
          return;
       }          

       Serial.print("Temperature: ");
       Serial.print(t);
       Serial.print(" degrees Celcius, Humidity: ");
       Serial.print(h);
       Serial.println("%");


        delay(3000); 
       }
        
