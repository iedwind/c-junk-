// Blynk IOT Smart Plant Monitoring System

/* Connections
Relay. D3
Btn.   D7
Soil.  A0
PIR.   D5
SDA.   D2
SCL.   D1
Temp.  D4
*/

#define BLYNK_TEMPLATE_ID "TMPL2nzj7A-dd"
#define BLYNK_TEMPLATE_NAME "MARIA JUANA"
//Include the library files
//#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//Initialize the LCD display
//LiquidCrystal_I2C lcd(0x3F, 16, 2);

char auth[] = "oMmtAYacYV5BaR-flHAwRBT5-93h2Dbm";
char ssid[] = "Totalplay-A0A3";
char pass[] = "Mustang1998";


DHT dht(D4, DHT11);//(DHT sensor pin,sensor type)  D4 DHT11 Temperature Sensor
BlynkTimer timer;

//Define component pins
//#define soil A0     //A0 Soil Moisture Sensor
//#define PIR D5      //D5 PIR Motion Sensor
//int PIR_ToggleValue;

void checkPhysicalButton();
//int relay1State = LOW;
int relay2State = LOW;
int relay3State = LOW;
int relay4State = LOW;
int pushButton1State = HIGH;
//#define RELAY_PIN_1       D3   //D3 Relay ~water pump
#define RELAY_PIN_2       D1   //D1 Relay~lights
#define RELAY_PIN_3       D2   //D2 Relay~fan 
#define RELAY_PIN_4       D5   //D5 Relay~Extractor
//#define PUSH_BUTTON_1     D7   //D7 Button not in use 
//#define VPIN_BUTTON_1    V12   //virtual button ~water pump
#define VPIN_BUTTON_2    V11   //virtual button ~ lights
#define VPIN_BUTTON_3    V10   //virtual button ~fan 
#define VPIN_BUTTON_4    V9    //virtual button ~extractor
//define SENSOR DHT11  	  D4   
//Create three variables for pressure
double T, P;
char status;



void setup() {
  Serial.begin(9600);
//  lcd.begin();
//  lcd.backlight();
//  pinMode(PIR, INPUT);
//had some outputs ~~
//WATER PUMP
 //pinMode(RELAY_PIN_1, OUTPUT);
 //digitalWrite(RELAY_PIN_1, LOW);
//LIGHTS
 pinMode(RELAY_PIN_2, OUTPUT);
 digitalWrite(RELAY_PIN_2, LOW);
//FAN
 pinMode(RELAY_PIN_3, OUTPUT);
 digitalWrite(RELAY_PIN_3, LOW);
//EXTRACTOR
 pinMode(RELAY_PIN_4, OUTPUT);
 digitalWrite(RELAY_PIN_4, LOW);
//physical button in D7 not in use ~
// pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
// digitalWrite(RELAY_PIN_1, relay1State);


  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  //lcd.setCursor(0, 0);
  //lcd.print("  Initializing  ");
  //for (int a = 5; a <= 10; a++) {
  //  lcd.setCursor(a, 1);
  //  lcd.print(".");
  //  delay(500);
  //}
  //lcd.clear();
  //lcd.setCursor(11, 1);
  //lcd.print("W:OFF");
  //Call the function
  //timer.setInterval(100L, soilMoistureSensor);
  timer.setInterval(100L, DHT11sensor);
  //timer.setInterval(500L, checkPhysicalButton);
}


//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  // lcd.setCursor(0, 0);
  // lcd.print("T:");
  // lcd.print(t);

  // lcd.setCursor(8, 0);
  // lcd.print("H:");
  // lcd.print(h);

}


// //Get the soil moisture values
// void soilMoistureSensor() {
//   int value = analogRead(soil);
//   value = map(value, 0, 1024, 0, 100);
//   value = (value - 100) * -1;

//   Blynk.virtualWrite(V3, value);
//   lcd.setCursor(0, 1);
//   lcd.print("S:");
//   lcd.print(value);
//   lcd.print(" ");

// }

//Get the PIR sensor values
// void PIRsensor() {
//   bool value = digitalRead(PIR);
//   if (value) {
//     Blynk.logEvent("pirmotion","WARNNG! Motion Detected!"); //Enter your Event Name
//     WidgetLED LED(V5);
//     LED.on();
//   } else {
//     WidgetLED LED(V5);
//     LED.off();
//   }  
//   }

// BLYNK_WRITE(V6)
// {
//  PIR_ToggleValue = param.asInt();  
// }


BLYNK_CONNECTED() {
  // Request the latest state from the server
 // Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
}

//BLYNK_WRITE(VPIN_BUTTON_1) {
//  relay1State = param.asInt();
//  digitalWrite(RELAY_PIN_1, relay1State);
//}
BLYNK_WRITE(VPIN_BUTTON_2) {
  relay2State = param.asInt();
  digitalWrite(RELAY_PIN_2, relay2State);
}
BLYNK_WRITE(VPIN_BUTTON_3) {
  relay3State = param.asInt();
  digitalWrite(RELAY_PIN_3, relay3State);
}
BLYNK_WRITE(VPIN_BUTTON_4) {
  relay4State = param.asInt();
  digitalWrite(RELAY_PIN_4, relay4State);
}


// void checkPhysicalButton()
// {
//   if (digitalRead(PUSH_BUTTON_1) == LOW) {
//     // pushButton1State is used to avoid sequential toggles
//     if (pushButton1State != LOW) {

//       // Toggle Relay state
//       relay1State = !relay1State;
//       digitalWrite(RELAY_PIN_1, relay1State);

//       // Update Button Widget
//       Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
//     }
//     pushButton1State = LOW;
//   } else {
//     pushButton1State = HIGH;
//   }
// }


void loop() {
//     if (PIR_ToggleValue == 1)
//     {
//     lcd.setCursor(5, 1);
//     lcd.print("M:ON ");
//       PIRsensor();
//       }
//      else
//      {
//     lcd.setCursor(5, 1);
//     lcd.print("M:OFF");
//     WidgetLED LED(V5);
//     LED.off();
//      }

// if (relay1State == HIGH)
// {
//   lcd.setCursor(11, 1);
//   lcd.print("W:ON ");
//   }
//   else if (relay1State == LOW)
//   {
//     lcd.setCursor(11, 1);
//     lcd.print("W:OFF");
//     }
     
      
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer

  }