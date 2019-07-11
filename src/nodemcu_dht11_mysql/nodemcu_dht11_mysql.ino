/*
  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Change the SSID and pass to match your WiFi network
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.

*/
#include <ESP8266WiFi.h>                        // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <DHT.h>                                // Including library for dht



#define DHTPIN 2                                // pin where the dht11 is connected (D4 NodeMCU V1)
#define DHTTYPE DHT11                           // defining which DHT sensor type

DHT dht(DHTPIN, DHTTYPE);                       // create dht11 instance


IPAddress server_addr(192,168,1,2);  // IP of the MySQL *server* here
char user[] = "bob";                 // MySQL user login username
char password[] = "secret";          // MySQL user login password
float sensor_value = 30;
String str = String(sensor_value); 


// WiFi card example
char ssid[] = "crepe et gaufre";         // your SSID
char pass[] = "crepes@gaufres";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only
  // Begin DHT module 
  dht.begin();
  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{

      float h = dht.readHumidity();
      float t = dht.readTemperature();
      char humidity[7];
      char temperature[6];
      char re [20];
      
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

       String temp_hum = String(t) + "', '" + String(h) + "');";
       //String(h).toCharArray(humidity, 7);
       //String(t).toCharArray(temperature, 6);  
       temp_hum.toCharArray(re, 20);
       //Serial.println(temperature);
       //Serial.println(humidity);
  
 
  // Sample query
  // char INSERT_SQL1[]   = "INSERT INTO testF.dht11 (temperature, humidity) VALUES ('24', '50');";
  //char INSERT_TEMPERATURE[]   = "INSERT INTO testF.dht11 (temperature) VALUES ('";
  char SQL[]   = "INSERT INTO testF.dht11 (temperature, humidity) VALUES ('";


  strcat(SQL, re);
  Serial.println(SQL);
  
  if (conn.connected()) {
    cursor->execute(SQL);
  }

  delay(10000);
}
