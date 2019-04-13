//Here we present a sketch that is coupled to a circuit containing a light dependent resistor 
//and a low cost sensor that reads temperature and humidity (DHT22). The data collected by 
//these sensors is then sent and read via our Adafruit IO. The DHT22 sensor data is sent to 
//individual humidity and temperature feeds while the light sensor information is sent to an
//analog feed. All three feeds are read on the same dashboard. 

//This is my AdafruitIO link: https://io.adafruit.com/rodrigoumanzor/dashboards/hcde-temperature-and-humidity 

#include "config.h" //Include code with information needed to connect to wifi and Adafruit IO
#include <Adafruit_Sensor.h> //Include sensor library 
#include <DHT.h> //Include DHT library 
#include <DHT_U.h>


#define DATA_PIN 12 // pin connected to DH22 data line
DHT_Unified dht(DATA_PIN, DHT22); // create DHT22 instance

#define PHOTOCELL_PIN A0 // Definbe the analog pin 0 for photocell 

int current = 1; // photocell state
int last = 0; 

// Set up the 'temperature', 'humidity', and 'Analog' feeds
AdafruitIO_Feed *temperature = io.feed("Temperature");
AdafruitIO_Feed *humidity = io.feed("Humidity");
AdafruitIO_Feed *analog = io.feed("Analog");

void setup() {

  // Start the serial connection
  Serial.begin(115200);

  // Wait for serial monitor to open
  while(! Serial);

  // Initialize dht22
  dht.begin();

  // Connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Let us know that we are connected
  Serial.println();
  Serial.println(io.statusText());
  
}

void loop() {

  io.run(); //Required at top of loop to keep client connected and to process incoming data

  sensors_event_t event;
  dht.temperature().getEvent(&event); //Get temeperature data

  float celsius = event.temperature; //Raw temperature data saved in celcius
  float fahrenheit = (celsius * 1.8) + 32; //Convert to degrees fahrenheit

  Serial.print("fahrenheit: ");
  Serial.print(fahrenheit);
  Serial.println("F");

  temperature->save(fahrenheit);  // Save fahrenheit to Adafruit IO

  dht.humidity().getEvent(&event); //Get humidity data

  Serial.print("humidity: ");
  Serial.print(event.relative_humidity);
  Serial.println("%");

  humidity->save(event.relative_humidity); // save humidity to Adafruit IO 
 

  // grab the current state of the photocell
  current = analogRead(PHOTOCELL_PIN);

  // return if the value hasn't changed
  if(current == last)
    return;

  // save the current state to the analog feed
  Serial.print("sending light data --> ");
  Serial.println(current);
  analog->save(current);

  // store last photocell state
  last = current;
 
  delay(5000); // wait 5 seconds (5000 milliseconds == 5 seconds)
}
