#include "DHT.h"

#define DHTPIN 4      // DHT11 connected to pin 4
#define DHTTYPE DHT11 // DHT11 sensor

DHT dht(DHTPIN, DHTTYPE); // Creates DHT object

void setup() {
  Serial.begin(9600); 
  dht.begin();        // Initializes/Starts sensor
}

void loop() {
  delay(2000); //  2 seconds wait between reads

  float humidity = dht.readHumidity(); //Sends signal to DHT11 looking for data of the humidity
  float temperature = dht.readTemperature(); //Sends signal to DHT11 looking for data of the temperature

  if (isnan(humidity) || isnan(temperature)) { //isnan = is not a number // checks to see if there is a temp/humidity number
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity (%): "); //prints humidity percent to serial monitor
  Serial.println(humidity, 2); // prints it with 2 decimal places

  Serial.print("Temperature (°C): "); //prints temperature celsius to serial monitor
  Serial.println(temperature, 2); // prints it with 2 decimal places

}
