/*
 * Jonathas Eide Fujii
 * jonathasfujii@gmail.com
 * 30/01/2017
 * 
 * Arduino IDE v1.8.0
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h> // http://pubsubclient.knolleary.net/

//// WIFI ////
const char* ssid = "";
const char* password = "";
const char* senha_ota = "";


//// MQTT ////
const char* mqtt_server = "192.168.1.16";
const char* mqtt_username = "";
const char* mqtt_password = "";
const char* client_id = "esp01-abajur"; // Must be unique on the MQTT network
const char* start_state_topic = "casa/abajur/start";
const char* ldr_state_topic = "casa/abajur/ldr";
const char* pir_state_topic = "casa/abajur/pir";
const char* light_state_topic = "casa/abajur/luz";
const char* light_set_topic = "casa/abajur/luz/set";
const char* on_cmd = "ON";
const char* off_cmd = "OFF";
const int BUFFER_SIZE = JSON_OBJECT_SIZE(10);

WiFiClient espClient;
PubSubClient client(espClient);

//// Sensor LDR ////
const byte pinLdr = A0;
int valueLdr = 0;
long timeLdr = 0;

//// Sensor PIR ////
const byte pinPir = 16;
byte pirOldState = LOW;
//const int sleepPir = 60;
//long lastTimerPir = 0;

//// Luz escurecer ////
const byte pinRed = 4;

// Maintained state for reporting to HA
byte red = 255;
byte brightness = 255;
// Real values to write to the LEDs (ex. including brightness and state)
byte realRed = 0;
bool stateOn = false;
// Globals for fade/transitions
bool startFade = false;
unsigned long lastLoop = 0;
int transitionTime = 0;
bool inFade = false;
int loopCount = 0;
int stepR;
int redVal;
// Globals for flash
bool flash = false;
bool startFlash = false;
int flashLength = 0;
unsigned long flashStartTime = 0;
byte flashRed = red;
byte flashBrightness = brightness;

//// Botão ////
//// Botão ////
const int debouncerTime = 200;
const byte pinBotao1 = 5;
byte readingBotao1 = HIGH;
byte botao1State = HIGH;
byte botao1OldState = HIGH;
long debounceTimeBotao1 = 0;


