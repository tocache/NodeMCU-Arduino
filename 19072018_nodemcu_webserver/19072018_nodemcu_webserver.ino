#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"
#include <LiquidCrystal.h>

#define DHT22_PIN 2
#define ssid      "Zoompoipoi"       // WiFi SSID
#define password  "zoompoipoipoi"  // WiFi password
#define LEDPIN    14         // Led
#define INPPIN    12        // Input

float   temperature = 0 ;
float   humidity = 0 ;
String  etatLed = "Off";
String  etatLed2 = "Off";
int i=0;

//Custom characters on the LCD 44780
byte grado2[8] = {
  B11000,
  B11000,
  B00110,
  B01001,
  B01000,
  B01000,
  B01001,
  B00110,
};

 byte termo[8] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

byte gota[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

byte iop[8] = {
  B11100,
  B01001,
  B01010,
  B11100,
  B00111,
  B01101,
  B10101,
  B00111
};

// Create Objects
const int rs = 9, en = 10, d4 = 0, d5 = 4, d6 = 5, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
ESP8266WebServer server ( 80 );
DHTesp dht;
 
String getPage(){
  String page = "<html lang=es-ES><head><meta http-equiv='refresh' content='10'/>";
  page += "<title>Tocache ESP8266 Demo</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  page += "<script type='text/javascript' src='http://www.webestools.com/ftp/ybouane/scripts_tutorials/javascript/date_time/date_time.js'></script>";
  page += "</head><body><h1>Tocache ESP8266 Demo</h1>";
  page += "<a href='https://ibb.co/bChiMy'><img src='https://preview.ibb.co/iPoeuJ/37383545_10217528414541426_5207107518039326720_n.jpg' alt='37383545_10217528414541426_5207107518039326720_n' border='0'></a>";
  page += "<h3>DHT22</h3>";
  page += "<ul><li>Temperature : ";
  page += temperature;
  page += " C</li>";
  page += "<li>Humidity : ";
  page += humidity;
  page += " %</li></ul>";
  page += "<h3>GPIO</h3>";
  page += "<form action='/' method='POST'>";
  page += "<ul><li>D6 Input (status: ";
  page += etatLed2;
  page += ")";
  page += "<li>D5 Output (status: ";
  page += etatLed;
  page += ")";
  page += "<INPUT type='radio' name='LED' value='1'>ON";
  page += "<INPUT type='radio' name='LED' value='0'>OFF</li></ul>";  
  page += "<INPUT type='submit' value='Update'>";
  page += "<br><br><span id='date_time'></span>";
  page += "<script type='text/javascript'>window.onload = date_time('date_time')</script>";
  page += "<p><a href='https://www.instagram.com/tocache'>Tocache Instagram</p>";
  page += "</body></html>";
  return page;
}

void handleRoot(){ 
  if ( server.hasArg("LED") ) {
    handleSubmit();
  } else {
    server.send ( 200, "text/html", getPage() );
  }  
}
 
void handleSubmit() {
  // Update GPIO 
  String LEDValue;
  LEDValue = server.arg("LED");
  Serial.print("Set GPIO "); Serial.println(LEDValue);
  if ( LEDValue == "1" ) {
    digitalWrite(LEDPIN, 1);
    etatLed = "On";
    server.send ( 200, "text/html", getPage() );
  } else if ( LEDValue == "0" ) {
    digitalWrite(LEDPIN, 0);
    etatLed = "Off";
    server.send ( 200, "text/html", getPage() );
  } else {
    Serial.println("Err Led Value");
  }
}
 
void setup() {
  pinMode(INPPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin ( 115200 );
  Serial.print("Starting");
  WiFi.begin ( ssid, password );
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 ); Serial.print ( "." );
  }
  // WiFi connexion is OK
  Serial.println ( "" ); 
  Serial.print ( "Connected to " ); Serial.println ( ssid );
  Serial.print ( "IP address: " ); Serial.println ( WiFi.localIP() );
 
  // link to the function that manage launch page 
  server.on ( "/", handleRoot );
 
  server.begin();
  Serial.println ( "HTTP server started" );
   
  dht.setup(2, DHTesp::DHT22);
  lcd.begin(16, 2);
  lcd.createChar(0, grado2);
  lcd.createChar(1, termo);
  lcd.createChar(2,gota);
  lcd.createChar(3,iop);
}
 
void loop() {
  server.handleClient();
  lcd.setCursor(0, 0);
  lcd.print("Tocache NodeMCU!");
  delay(dht.getMinimumSamplingPeriod());
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
  delay(70);
  Serial.print("Temperatura = ");
  Serial.print(temperature, 1);
  Serial.println(" C");
  Serial.print("Humedad = ");
  Serial.print(humidity, 1);
  Serial.println(" %");
  lcd.setCursor(0, 1);
  //lcd.print("T:");
  lcd.write(byte(1));
  lcd.print(temperature, 1);
  lcd.write(byte(0));
  //lcd.write(0xDF);
  //lcd.print("C");
  lcd.setCursor(7, 1);  
  //lcd.print("H:");
  lcd.write(byte(2));
  lcd.print(humidity, 1);
  lcd.print("%");
  lcd.setCursor(14, 1);
  lcd.write(byte(3));
  if ( digitalRead(INPPIN) == 0 ) {
    etatLed2 = "Off";
    lcd.print("0");
  } else {
    etatLed2 = "On";
    lcd.print("1");
  }
  //delay(100);
  i=i+1;
  if(i==10){
      slot();
      i=0;
  }
}

void slot() {
  lcd.clear();
  lcd.print("Refreshing");
  lcd.setCursor(0,1);
  lcd.print("IP:");
  lcd.print( WiFi.localIP() );
  for(int j=0;j<10;j++) {
    lcd.setCursor(11,0);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.print(j);
    lcd.setCursor(11,1);
    delay(250);
  }
  delay(1000);
  lcd.clear();
}

