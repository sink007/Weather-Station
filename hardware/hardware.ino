//##################################################################################################################
//##                                      ELET2415 DATA ACQUISITION SYSTEM CODE                                   ##
//##                                                                                                              ##
//##################################################################################################################

// LIBRARY IMPORTS
#include <rom/rtc.h> 
#include <math.h>  // https://www.tutorialspoint.com/c_standard_library/math_h.htm 
#include <ctype.h>

// IMPORTS
#include <DHT.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_BMP280.h>

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

// DEFINE VARIABLES
#define ARDUINOJSON_USE_DOUBLE      1 

#define DHT_pin 15
#define DHTTYPE DHT22 
#define soil 36
#define TFT_DC    17
#define TFT_CS    5
#define TFT_RST   16
#define TFT_CLK   18
#define TFT_MOSI  23
#define TFT_MISO  19

#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h> 
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h> 


// MQTT CLIENT CONFIG  
static const char* pubtopic      = "620155784";                    // Add your ID number here
static const char* subtopic[]    = {"620155784_sub","/elet2415"};  // Array of Topics(Strings) to subscribe to
static const char* mqtt_server   = "broker.hivemq.com";         // Broker IP address or Domain name as a String 
static uint16_t mqtt_port        = 1883;

// WIFI CREDENTIALS
const char* ssid       = "Hello";     // Add your Wi-Fi ssid
const char* password   = "family123"; // Add your Wi-Fi password 


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
 

/* Declare your functions below */ 
double convert_Celsius_to_fahrenheit(double c);
double convert_fahrenheit_to_Celsius(double f);
double calcHeatIndex(double Temp, double Humid);


/* Init class Instances*/
DHT dht(DHT_pin, DHTTYPE);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Adafruit_BMP280 bmp; 


//############### IMPORT HEADER FILES ##################
#ifndef NTP_H
#include "NTP.h"
#endif

#ifndef MQTT_H
#include "mqtt.h"
#endif

// Temporary Variables 
double value; //analog value from soil sensor
double soilMoisture; //soil mositure %
double hum; //humidity
double temp; 
double far; //temp in fahrenheit
double heatindex; 
double pressure; 
double alt; //altitude
const double c1 = -42.379;
const double c2 = 2.04901523;
const double c3 = 10.14333127;
const double c4 = -0.22475541;
const double c5 = -6.83783e-03;
const double c6 = -5.481717e-02;
const double c7 = 1.22874e-03;
const double c8 = 8.5282e-04;
const double c9 = -1.99e-06;
const int dry = 3600; // value for air
const int wet = 1600; // value for water

  
void setup() {
  Serial.begin(115200);  // INIT SERIAL  
  bmp.begin(0x76);
  dht.begin();
  tft.begin();
  tft.setRotation(3); // Rotate the display to default orientation
  tft.fillScreen(ILI9341_BLACK); // Clear the screen

   // Set up the title and background
  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(75, 35); 
  tft.println("Weather Station");
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(20, 65);
  tft.println("Done by: L.Hines");

  tft.drawRect(20, 85, 285, 150, ILI9341_WHITE); // Shifted up by 15 pixels

  // Set up the text for displaying sensor values
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(30, 113); 
  tft.print("Temperature: ");
  tft.setCursor(30, 133); 
  tft.print("Humidity: ");
  tft.setCursor(30, 153);
  tft.print("Heat Index: ");
  tft.setCursor(30, 173); 
  tft.print("Soil Moisture: ");
  tft.setCursor(30, 193); 
  tft.print("Pressure: ");
  tft.setCursor(30, 213); 
  tft.print("Altitude: ");

  initialize();     // INIT WIFI, MQTT & NTP 
  //vButtonCheckFunction(); // UNCOMMENT IF USING BUTTONS INT THIS LAB, THEN ADD LOGIC FOR INTERFACING WITH BUTTONS IN THE vButtonCheck FUNCTION
 }
  


void loop() {
    // put your main code here, to run repeatedly:    
   
    vTaskDelay(1000 / portTICK_PERIOD_MS);    
}




  
//####################################################################
//#                          UTIL FUNCTIONS                          #       
//####################################################################
void vButtonCheck( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );     
      
    for( ;; ) {
        

        vTaskDelay(200 / portTICK_PERIOD_MS);  
    }
}

void vUpdate( void * pvParameters )  {
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );    
           
    for( ;; ) {
          // #######################################################
          // ## This function must PUBLISH to topic every second. ##
          // #######################################################
   
          value = analogRead(soil);
          soilMoisture = map(value,dry,wet,0,100);
          if (soilMoisture>100){
            soilMoisture= 100;
          }
          else if(soilMoisture<0){
            soilMoisture=0;
          }
          hum = dht.readHumidity();
          temp = dht.readTemperature();
          far = convert_Celsius_to_fahrenheit(temp);
          heatindex = convert_fahrenheit_to_Celsius(calcHeatIndex(far,hum)); 
          pressure= bmp.readPressure()/1000;
          alt= bmp.readAltitude(1012.3);
          
          tft.fillRect(150, 90, 151, 140, ILI9341_BLACK); // Clear the box 
          tft.setCursor(150, 113); 
          tft.print(temp);
          tft.println(" C");
          tft.setCursor(150, 133); 
          tft.print(hum);
          tft.println(" %");
          tft.setCursor(150, 153); 
          tft.print(heatindex);
          tft.println(" C");
          tft.setCursor(150, 173); 
          tft.print(soilMoisture);
          tft.println(" %");
          tft.setCursor(150, 193); 
          tft.print(pressure);
          tft.println(" kPa");
          tft.setCursor(150, 213); 
          tft.print(alt);
          tft.println(" m");
          
          // ##Publish update according to ‘{"id": "student_id", "timestamp": 1702212234, "temperature": 30, "humidity":90, "heatindex": 30, "pressure":30, "altitude": 30, "soilMoisture": 30}’
          // 1. Create JSon object
          StaticJsonDocument<1000> doc; // Create JSon object
          
          // 2. Create message buffer/array to store serialized JSON object
          char message[900]  = {0};

          // 3. Add key:value pairs to JSon object based on above schema
          doc["id"]         = "620155784"; // Change to your student ID number
          doc["timestamp"]  = getTimeStamp();
          doc["temperature"]= temp;
          doc["humidity"]= hum;
          doc["heatindex"]= heatindex;
          doc["pressure"]= pressure; 
          doc["altitude"]= alt;
          doc["soilMoisture"]= soilMoisture; 

          // 4. Seralize / Covert JSon object to JSon string and store in message array
          serializeJson(doc, message);
        
          // 5. Publish message to a topic sobscribed to by both backend and frontend                
          publish(pubtopic, message);

          vTaskDelay(2000 / portTICK_PERIOD_MS);  
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

 
  // CONVERT MESSAGE TO JSON
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, received);  

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }


  // PROCESS MESSAGE
  const char* type = doc["type"]; 

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

//***** Complete the util functions below ******

double convert_Celsius_to_fahrenheit(double c){    
    // CONVERTS INPUT FROM °C TO °F. RETURN RESULTS   
    return ((c * 9 / 5) + 32);
}

double convert_fahrenheit_to_Celsius(double f){    
    // CONVERTS INPUT FROM °F TO °C. RETURN RESULT    
    return ((f-32) * 5/ 9);
}

double calcHeatIndex(double T, double H){
    // CALCULATE AND RETURN HEAT INDEX USING EQUATION FOUND AT https://byjus.com/heat-index-formula/#:~:text=The%20heat%20index%20formula%20is,an%20implied%20humidity%20of%2020%25
  
  return  c1 + (c2 * T) + (c3 * H) + (c4 * T * H) + (c5 * T * T) + (c6 * H * H) + (c7 * T * T * H) + (c8 * T * H * H) + (c9 * T * T * H * H);
  //return dht.computeHeatIndex(T, H, false);
}
 