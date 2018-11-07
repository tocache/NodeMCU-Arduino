#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define ssid      "UPC_Mamadera"       // WiFi SSID
#define password  "607000698"  // WiFi password
#define LEDPIN    16         // Led
#define LEDPIN2   16        // Led2

String  etatLed = "Off";
String  etatLed2 = "Off";

// Create Objects
ESP8266WebServer server ( 80 );
IPAddress apIP(192, 168, 4, 42);
 
String getPage(){
  String page = "<html lang=es-ES><head><meta http-equiv='refresh' content='10'/>";
  page += "<title>UPC IoT Server</title>";
  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  page += "<script type='text/javascript' src='http://www.webestools.com/ftp/ybouane/scripts_tutorials/javascript/date_time/date_time.js'></script>";
  page += "</head><body><h1>UPC IoT Server</h1>";
  page += "<h3>GPIO</h3>";
  page += "<form action='/' method='POST'>";
  page += "<li>D0 Output (status: ";
  page += etatLed;
  page += ")";
//  page += "<INPUT type='radio' name='LED' value='1'>ON";
//  page += "<INPUT type='radio' name='LED' value='0'>OFF</li></ul>";  
//  page += "<INPUT type='submit' value='Update'>";
  page += "<INPUT type='button' name='LED' value='1'>ON";
  page += "<INPUT type='button' name='LED' value='0'>OFF";
  page += "<p><a href='\LED2On\'><button>ON2</button></a><a href=\"LED2Off\"><button>OFF2</button></a></p>";
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
  pinMode(LEDPIN, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  digitalWrite(LEDPIN2, LOW);
  Serial.begin ( 115200 );
  Serial.print("Starting");

  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
    
  // link to the function that manage launch page 
  server.on ( "/", handleRoot );
 
  server.begin();
  Serial.println ( "HTTP server started" );
   
}
 
void loop() {
  server.handleClient();
  delay(70);

  //delay(100);
  
}


