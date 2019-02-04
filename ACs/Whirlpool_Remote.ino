#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>
#include <ir_Whirlpool.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRWhirlpoolAc ac(kIrLed);
const char* ssid = "USERNAME";
const char* password = "PASSWORD";
MDNSResponder mdns;

ESP8266WebServer server(80);

IRsend irsend(4);  // An IR LED is controlled by GPIO pin 4 (D2)
int te=24;
void printState() {
  // Display the settings.
  Serial.println("Whirlpool A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  // Display the encoded IR sequence.
  unsigned char* ir_code = ac.getRaw();
  Serial.print("IR Code: 0x");
  Serial.println();
}



void handleRoot() {
  server.send(200, "text/html",
              "<html>" \
                "<head><title>ESP8266 Demo</title></head>" \
                "<body>" \
                  "<h1>Hello from ESP8266, you can send NEC encoded IR" \
                      "signals from here!</h1>" \
                  "<p><a href=\"ir?code=2704\">Send ON</a></p>" \
                  "<p><a href=\"ir?code=27\">Send temp_down</a></p>" \
                  "<p><a href=\"ir?code=222\">Send temp_up</a></p>" \
                  "<p><a href=\"ir?code=2709\">Send OFF</a></p>" \
  "<p><a href=\"ir?code=30\">Set Mode Auto</a></p>" \
  "<p><a href=\"ir?code=31\">Set Mode Dry</a></p>" \
  "<p><a href=\"ir?code=32\">Set Mode Cool</a></p>" \
  "<p><a href=\"ir?code=33\">Set Mode Fan</a></p>" \
  "<p><a href=\"ir?code=40\">Set fan mode Auto</a></p>" \
  "<p><a href=\"ir?code=41\">Set fan mode High</a></p>" \
  "<p><a href=\"ir?code=42\">Set fan mode Medium</a></p>" \
  "<p><a href=\"ir?code=43\">Set fan mode Low</a></p>" \
  "<p><a href=\"ir?code=44\">Set fan mode Auto2</a></p>" \
  "<p><a href=\"ir?code=50\">Set Swing Move</a></p>" \
  "<p><a href=\"ir?code=51\">Set Swing Mask</a></p>" \
                "</body>" \
              "</html>");
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 10);
      if(code == 2704) // On
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);

  // Set up what we want to send. See ir_Fujitsu.cpp for all the options.
  Serial.println("Default state of the remote.");
  //printstate();
  Serial.println("Setting desired state for A/C.");
  ac.setPowerToggle(1);
  ac.setSwing(kWhirlpoolAcSwing2Mask);
  ac.setMode(kWhirlpoolAcAuto);
  ac.setFan(kWhirlpoolAcFanAuto);
  ac.setTemp(te);  // 24C
    ac.send();}
    
      if(code == 2709) //OFF
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);

 
  Serial.println("Default state of the remote.");
  //printstate();
  Serial.println("Setting desired state for A/C.");
  ac.setPowerToggle(0);
    ac.send();}

      if(code == 222) //TEMP_UP 
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
te++;
ac.setTemp(te);  // 24C
    ac.send();}

      if(code == 27) //TEMP_DOwN
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
te--;
  ac.setTemp(te); 
    ac.send();}
    
if(code == 30) //MODE_AUTO
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcAuto);
    ac.send();}


if(code == 31) //MODE_DRY
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcDry);
    ac.send();}

    
if(code == 32) //MODE_COOL
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcCool);
    ac.send();}



if(code == 33) //MODE_FAN
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
    ac.send();}



if(code == 40) //FAN_AUTO
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
  ac.setFan(kWhirlpoolAcFanAuto);
    ac.send();}


if(code == 41) //FAN_HIGH
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
  ac.setFan(kWhirlpoolAcFanHigh);
    ac.send();}

if(code == 42) //FAN_medium
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
  ac.setFan(kWhirlpoolAcFanMedium);
    ac.send();}

if(code == 43) //FAN_low
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
  ac.setFan(kWhirlpoolAcFanLow);
    ac.send();}





if(code == 44) //FAN_Auto
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setMode(kWhirlpoolAcFan);
  ac.setFan(kWhirlpoolAcFanAuto);
    ac.send();}



  if(code == 50) //Swing_Mask
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setSwing(kWhirlpoolAcSwing2Mask);
    ac.send();}


  if(code == 51) //Swing_Move
      {
  ac.begin();
  Serial.begin(115200);
  delay(200);
  ac.setSwing(kWhirlpoolAcSwing1Mask);
    ac.send();}



    
     
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
