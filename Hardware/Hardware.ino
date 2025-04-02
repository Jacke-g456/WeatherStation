
#include <rom/rtc.h> 
#include <math.h>  // https://www.tutorialspoint.com/c_standard_library/math_h.htm 
#include <ctype.h>

// ADD YOUR IMPORTS HERE
#include <PubSubClient.h>

#ifndef _WIFI_H 
#include <WiFi.h>
#endif


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

//############### IMPORT HEADER FILES ##################

// Temperature sennsor constants
#define DHTpin 4
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

bool is_Far=false;
#define btn1 33

// Temperature sennsor functions
double convert_Celsius_to_fahrenheit(double c);
double convert_fahrenheit_to_Celsius(double f);
double calcHeatIndex(double Temp, double Humid);

/* Init class Instances for the DHT22 etcc */
DHT dht(DHTpin, DHTTYPE);


// background
void drawGradientBackground() {
  for (int y = 0; y < tft.height(); y++) {
    uint16_t color = tft.color565(0, y / 2, 255 - (y / 2)); // Blue gradient
    tft.drawFastHLine(0, y, tft.width(), color);
  }
}

// MQTT CLIENT CONFIG  
static const char* pubtopic       = "620165845";                    // Add your ID number here
static const char* subtopic[]     = {"620165845_sub","/elet2415"};  // Array of Topics(Strings) to subscribe to
static const char* mqtt_server    = "www.yanacreations.com";                // Broker IP address or Domain name as a String 
static uint16_t mqtt_port         = 1883;

// WIFI CREDENTIALS
const char* ssid                  = "iPhone (8)"; // Add your Wi-Fi ssid
const char* password              = "Steviecool-16"; // Add your Wi-Fi password 

// TASK HANDLES 
TaskHandle_t xMQTT_Connect          = NULL; 
TaskHandle_t xNTPHandle             = NULL;  
TaskHandle_t xLOOPHandle            = NULL;  
TaskHandle_t xUpdateHandle          = NULL;
TaskHandle_t xButtonCheckeHandle    = NULL; 

// FUNCTION DECLARATION   
void checkHEAP(const char* Name);   // RETURN REMAINING HEAP SIZE FOR A TASK
void initMQTT(void);                // CONFIG AND INITIALIZE MQTT PROTOCOL
unsigned long getTimeStamp(void);   // GET 10 DIGIT TIMESTAMP FOR CURRENT TIME
void callback(char* topic, byte* payload, unsigned int length);
void initialize(void);
bool publish(const char *topic, const char *payload); // PUBLISH MQTT MESSAGE(PAYLOAD) TO A TOPIC
void vButtonCheck( void * pvParameters );
void vUpdate( void * pvParameters ); 
void GDP(void);   // GENERATE DISPLAY PUBLISH

#ifndef NTP_H
#include "NTP.h"
#endif

#ifndef MQTT_H
#include "mqtt.h"
#endif



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
  pinMode(btn1, INPUT_PULLUP);

  initialize();
  vButtonCheckFunction();


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


  
  

   vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void vUpdate( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );    
           
    for( ;; ) {
     /* Serial.print("Air temperature: ");
  Serial.print(tft_temp);
  Serial.println(" °C");
  
  Serial.print("Heat Index: ");
  Serial.print(tft_heatindex);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(tft_humidity);
  Serial.println(" %");
  
  Serial.print("Air pressure: ");
  Serial.print(tft_pressure);
  Serial.println(" kPa");
  
  Serial.print("Altitude: ");
  Serial.print(tft_altitude);
  Serial.println(" m");

  Serial.print("Soil Moisture: ");
  Serial.print(tft_moisture);
  Serial.println(" %");

  Serial.println("-------------------");*/
  delay(2000); // Wait 2 seconds between readings
      if (isNumber(tft_temp)){
          // Task code goes here.   
          // PUBLISH to topic every second.
          JsonDocument doc; // Create JSon object
          char message[1100]  = {0};
          //tft_temp, tft_humidity, tft_heatindex, tft_pressure, tft_altitude;
          // Add key:value pairs to JSon object
          doc["id"]         = "620165845";
          doc["timestamp"]  = getTimeStamp();
          doc["temperature"] = tft_temp;
          doc["humidity"] = tft_humidity;
          doc["heatindex"] = tft_heatindex;
          doc["pressure"] = tft_pressure;
          doc["altitude"] = tft_altitude;
          doc["moisture"] = tft_moisture;

          serializeJson(doc, message);  // Seralize / Covert JSon object to JSon string and store in char* array

          if(mqtt.connected() ){
            publish(pubtopic, message);
          }
    }
            
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}


void vButtonCheck( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );     
      
    for( ;; ) {
        // Add code here to check if a button(S) is pressed
        if (digitalRead( btn1) == LOW){
          // then execute appropriate function if a button is pressed
          is_Far=!is_Far;

        }
          

        vTaskDelay(200 / portTICK_PERIOD_MS);  
    }
}

unsigned long getTimeStamp(void) {
          // RETURNS 10 DIGIT TIMESTAMP REPRESENTING CURRENT TIME
          time_t now;         
          time(&now); // Retrieve time[Timestamp] from system and save to &now variable
          return now;
}

void callback(char* topic, byte* payload, unsigned int length) {
  // ############## MQTT CALLBACK  ######################################
  // RUNS WHENEVER A MESSAGE IS RECEIVED ON A TOPIC SUBSCRIBED TO
  
  Serial.printf("\nMessage received : ( topic: %s ) \n",topic ); 
  char *received = new char[length + 1] {0}; 
  
  for (int i = 0; i < length; i++) { 
    received[i] = (char)payload[i];    
  }

  // PRINT RECEIVED MESSAGE
  Serial.printf("Payload : %s \n",received);

}

bool publish(const char *topic, const char *payload){   
     bool res = false;
     try{
        res = mqtt.publish(topic,payload);
        // Serial.printf("\nres : %d\n",res);
        if(!res){
          res = false;
          throw false;
        }
     }
     catch(...){
      Serial.printf("\nError (%d) >> Unable to publish message\n", res);
     }
  return res;
}


bool isNumber(double number){       
        char item[20];
        snprintf(item, sizeof(item), "%f\n", number);
        if( isdigit(item[0]) )
          return true;
        return false; 
} 


void Display_temp(double temp){
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
  tft.setCursor(0, 60);
  tft.print("Air Temp:");
  if (is_Far==true){
    tft.print(convert_Celsius_to_fahrenheit(temp));
    tft.print(" "); 
    tft.print((char)247); 
    tft.print("F");
    
  }
  else {
  tft.print(temp);
  tft.print(" "); 
  tft.print((char)247); 
  tft.print("C");}
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
  if (is_Far==true){
    tft.print(convert_Celsius_to_fahrenheit(index));
    tft.print(" "); 
    tft.print((char)247); 
    tft.print("F");
    
  }
  else {
  tft.print(index);
  tft.print(" "); 
  tft.print((char)247); 
  tft.print("C");}

  
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
