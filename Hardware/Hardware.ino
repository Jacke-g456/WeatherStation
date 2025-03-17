#include <math.h>  // https://www.tutorialspoint.com/c_standard_library/math_h.htm 
#include <ctype.h>

// ADD YOUR IMPORTS HERE
#include <PubSubClient.h>



#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif

#ifndef ARDUINO_H
#include <Arduino.h>
#endif 
 
#ifndef ARDUINOJSON_H
#include <ArduinoJson.h>
#endif

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


#include "DHT.h"

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// Temperature sennsor constants
#define DHTpin 27
#define DHTTYPE DHT22


//Pressure sensor constants
Adafruit_BMP280 bmp;

 

//soil constant
#define SoilPin A4

// TFT pins
#define TFT_DC    17 // 
#define TFT_CS    5
#define TFT_RST   16
#define TFT_CLK   18 //
#define TFT_MOSI  23
#define TFT_MISO  19

//tft instance
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//tft variables
double tft_temp, tft_humidity, tft_heatindex, tft_pressure, tft_altitude;
int tft_moisture;

// TFT util Functions' declarations
void Display_temp(double temp); // displays air temperature on the TFT
void Display_humid(double humid); // displays humidity on the TFT
void Display_heatindex(double index) ; // displays heatindex on the TFT
void Display_alt(double alt) ; // displays altitude on the TFT
void Display_pressure(double pressure) ; // displays air pressure on the TFT
void Display_moist(int moist) ; // displays soil moisture on the TFT



// Temperature sennsor functions
double convert_Celsius_to_fahrenheit(double c);
double convert_fahrenheit_to_Celsius(double f);
double calcHeatIndex(double Temp, double Humid);

/* Init class Instances for the DHT22 etcc */
DHT dht(DHTpin, DHTTYPE);

void drawGradientBackground() {
  for (int y = 0; y < tft.height(); y++) {
    uint16_t color = tft.color565(0, y / 2, 255 - (y / 2)); // Blue gradient
    tft.drawFastHLine(0, y, tft.width(), color);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  bmp.begin(0x76);
  bmp.setSampling(
  Adafruit_BMP280::MODE_NORMAL,    // Normal mode (cycled measurements)
  Adafruit_BMP280::SAMPLING_X2,    // Temperature oversampling
  Adafruit_BMP280::SAMPLING_X16,   // Pressure oversampling
  Adafruit_BMP280::FILTER_X16,     // Noise filtering
  Adafruit_BMP280::STANDBY_MS_500  // Standby time
);

  tft.begin();
  tft.setRotation(2);
   drawGradientBackground();
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(30, 10);
  tft.print("Weather Station");
  tft.fillRect(30, 30, 180, 3, ILI9341_WHITE);



}

void loop() {
  // put your main code here, to run repeatedly:
  double temp = dht.readTemperature(); 
  double humidity = dht.readHumidity();
  double heatindex = convert_fahrenheit_to_Celsius(calcHeatIndex(convert_Celsius_to_fahrenheit(temp), humidity));
  double altitude =  abs(bmp.readAltitude(1013.25));
  double pressure = bmp.readPressure()/1000;

  int sensorValue= analogRead(SoilPin);
  int moisture=map(sensorValue, 3300, 1500, 0, 100);


  
  if (tft_temp !=temp){
    Display_temp(temp);
    tft_temp =temp;
  }
  if (tft_heatindex !=heatindex){
    Display_heatindex(heatindex);
    tft_heatindex =heatindex;
  }

  if (tft_humidity !=humidity){
    Display_humid(humidity);
    tft_humidity =humidity;
  }
  
  if (tft_pressure !=pressure){
    Display_pressure(pressure);
    tft_pressure =pressure;
  }

  if (tft_altitude !=altitude){
    Display_alt(altitude);
    tft_altitude =altitude;
  }
  if (moisture>100)
  {
    moisture=100;
  }
  if (moisture<0){
    moisture=0;
  }
  if (tft_moisture !=moisture){
    Display_moist(moisture);
    tft_moisture =moisture;
  }


  
  Serial.print("Air temperature: ");
  Serial.print(temp);
  Serial.println(" °C");
  
  Serial.print("Heat Index: ");
  Serial.print(heatindex);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.print("Air pressure: ");
  Serial.print(pressure);
  Serial.println(" kPa");
  
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.print("Soil Moisture: ");
  Serial.print(moisture);
  Serial.println(" %");

  Serial.println("-------------------");
  delay(2000); // Wait 2 seconds between readings
}


void Display_temp(double temp){
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setCursor(0, 60);
  tft.print("Air Temp:");
  tft.print(temp);
  tft.print(" "); 
  tft.print((char)247); 
  tft.print("C");
}
void Display_humid(double humid){
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  
  tft.setCursor(0, 140);
  tft.print("Humidity:");
  tft.print(humid);
  tft.print(" %");
}
void Display_heatindex(double index){
  tft.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
  tft.setCursor(0, 100);
  tft.print("Heat Index:");
  tft.print(index);
  tft.print(" ");
  tft.print((char)247); 
  tft.print("C");
}
void Display_pressure(double pressure){
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
  tft.setCursor(0, 180);
  tft.print("Pressure:");
  tft.print(pressure);
  tft.print(" kPa");
}
void Display_alt(double alt){
  tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
  tft.setCursor(0, 220);
  tft.print("Altitude:");
  tft.print(alt,1);
  tft.print(" m");
}
void Display_moist(int moist){
  tft.setTextColor(ILI9341_ORANGE,ILI9341_BLACK);
  tft.setCursor(0, 260);
  tft.print("Soil Moisture:");
  tft.print(moist);
  tft.print(" %");
}


// Temperature Utility Functions
double convert_Celsius_to_fahrenheit(double c){    
    // CONVERTS INPUT FROM °C TO °F. RETURN RESULTS  
    return (c*9/5)+32; 
}

double convert_fahrenheit_to_Celsius(double f){    
    // CONVERTS INPUT FROM °F TO °C. RETURN RESULT 
    return (f-32)*5/9;   
}

double calcHeatIndex(double Temp, double Humid){
    // CALCULATE AND RETURN HEAT INDEX USING EQUATION FOUND AT https://byjus.com/heat-index-formula/#:~:text=The%20heat%20index%20formula%20is,an%20implied%20humidity%20of%2020%25
  return  -42.379 + (2.04901523 * Temp) + (10.14333127 * Humid) + (-0.22475541 * Temp * Humid) + (-0.00683783 * Temp * Temp) + (-0.05481717 * Humid * Humid) + (0.00122874 * Temp * Temp * Humid) + (0.00085282 * Temp * Humid * Humid)  + (-0.00000199 * Temp * Temp * Humid * Humid);
}
