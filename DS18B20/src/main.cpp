// I Petar Kirkov, 000800914 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else.

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the DS18B20 is connected to
const int oneWireBus = D3;

// String that contains judgement based on temperature
String judgement;

// Instance of OneWire used to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass the OneWire reference to the DallasTemperature object
DallasTemperature DS18B20(&oneWire);

// The DeviceAddress of the temperature sensor
DeviceAddress deviceAddress;

void setup()
{

  Serial.begin(115200); // Configure USB serial monitor

  DS18B20.begin(); // Start the DS18B20 sensor

  Serial.println("\n\nTemperature Application");

  // If the device address cannot be found (no temperature sensor plugged in)
  if (!DS18B20.getAddress(deviceAddress, 0))
  {
    Serial.println("No DS18B20 temperature sensors are installed!");
  }

  // The temperature sensor is found
  else
  {
    // String that will contain the device address
    String address = "";

    // Iterate through the device address array 
    for (byte s : deviceAddress)
      address += String(s, HEX); // Concat each byte to the address string as a hexadecimal value

    Serial.println("Found DS18B20 sensor with address: " + address);
  }
}

void loop()
{
  // Float variable which holds the temperature value
  float temp;

  // Request the temperature from the DS18B20 sensor
  DS18B20.requestTemperatures();

  // Get the temperature and assign it to the temp variable
  temp = DS18B20.getTempCByIndex(0);

  // If the temperature sensor is connected to the board
  if (DS18B20.getAddress(deviceAddress, 0))
  {
    // Set judgement to cold if the temperature is less than 10 degrees
    if (temp < 10)
      judgement = "Cold!"; // Set judgement to cold

    // Set judgement to cool if temperature falls between the range of 10-15 degrees
    else if (temp >= 10 && temp <= 15)
      judgement = "Cool"; // Set judgement to cool

    // Set judgement to perfect if temperature falls between the range of 15-25 degrees
    else if (temp >= 15 && temp <= 25)
      judgement = "Perfect"; 

    // Set judgement to warm if temperature falls between the range of 25-30 degrees
    else if (temp >= 25 && temp <= 30)
      judgement = "Warm";

    // Set judgement to hot if temperature falls between the range of 30-35 degrees
    else if (temp >= 30 && temp <= 35)
      judgement = "Hot";

    // Set judgement to too hot if temperature is over 35 degrees 
    else
      judgement = "Too Hot!";

    // Output a message with the current temperature and judgement
    Serial.println("Current temperature is: " + String(temp) + "° C or " + judgement);
  }

  // 5000ms (5 sec) delay
  delay(5000);
}