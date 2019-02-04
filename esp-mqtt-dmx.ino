
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <PubSubClient.h>
#include <espDMX.h>
#include <WebSocketsServer.h>

// WIFI Config Variables
const char* host = "esp-mqtt-dmx";
const char* ssid = "RZL-hardcore";
const char* password = "affeaffeaffeaffeaffeaffe00";
const char* mqtt_server = "infra.rzl.so";

//DMX Config
#define STATUS_LED_PIN 4
#define NUM_LIGHTS  2
unsigned int fadespeed = 20;

// Starting Addresses of PAR-Lights and Strobes (-1 because indexes start at 0)
const byte parAddr[NUM_LIGHTS] = {9, 19};
const byte strobeAddr[1] = {1};

// Channels of PAR Lights as offset to starting address
const byte parLum = 0;
const byte parR = 1;
const byte parG = 2;
const byte parB = 3;
const byte parFadeSpeed = 7;

// Channels for Strobe as offset to stating address
const byte strobeFreq = 0;
const byte strobeLum = 1;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
ESP8266WebServer httpServer(80);
WebSocketsServer webSocketServer = WebSocketsServer(81);
ESP8266HTTPUpdateServer httpUpdater;

byte dmxState[255] = {0};
byte dmxStateTarget[255] = {0};
long now, last = 0;


// Function declarations
void mqtt_reconnect();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void webSocket_event(uint8_t num, WStype_t type, uint8_t * payload, size_t length);


void setup() {
  Serial.begin(115200);
  setup_wifi();
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  webSocketServer.begin();
  webSocketServer.onEvent(webSocket_event);

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqtt_callback);

  dmxB.begin(STATUS_LED_PIN);
  dmxB.setChans(dmxState, 512);
  randomSeed(analogRead(0));
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void mqtt_reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(WiFi.macAddress().c_str())) {
      Serial.println("connected");
      mqttClient.subscribe("/dmx/push");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void webSocket_event(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if (type == WStype_TEXT){
    for(int i = 0; i < length; i++) Serial.print((char) payload[i]);
    Serial.println();
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  webSocketServer.broadcastTXT(payload, length);
  Serial.println();

  //**********************************************************************************
  if (strncmp("fadealltoblack",(char*)payload, 14) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = 0;  //luminance
      dmxStateTarget[parAddr[i]+parR] = 0; // red
      dmxStateTarget[parAddr[i]+parG] = 0; // green
      dmxStateTarget[parAddr[i]+parB] = 0; // blue
    }
  }
  //**********************************************************************************
  if (strncmp("fadealltowhite",(char*)payload, 14) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = 255;  //luminance
      dmxStateTarget[parAddr[i]+parR] = 255; // red
      dmxStateTarget[parAddr[i]+parG] = 255; // green
      dmxStateTarget[parAddr[i]+parB] = 255; // blue
    }
  }
  //**********************************************************************************
  if (strncmp("fadealltored",(char*)payload, 12) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = 255;  //luminance
      dmxStateTarget[parAddr[i]+parR] = 255; // red
      dmxStateTarget[parAddr[i]+parG] = 0; // green
      dmxStateTarget[parAddr[i]+parB] = 0; // blue
    }
  }
  //**********************************************************************************
  if (strncmp("fadealltoblue",(char*)payload, 13) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = 255;  //luminance
      dmxStateTarget[parAddr[i]+parR] = 0; // red
      dmxStateTarget[parAddr[i]+parG] = 0; // green
      dmxStateTarget[parAddr[i]+parB] = 255; // blue
    }
  }
  //**********************************************************************************
  if (strncmp("fadealltogreen",(char*)payload, 14) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = 255;  //luminance
      dmxStateTarget[parAddr[i]+parR] = 0; // red
      dmxStateTarget[parAddr[i]+parG] = 255; // green
      dmxStateTarget[parAddr[i]+parB] = 0; // blue
    }
  }
  //**********************************************************************************
  if (strncmp("cycleallrandom",(char*)payload, 14) == 0) {
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxStateTarget[parAddr[i]+parLum] = random(50,256);  //luminance
      dmxStateTarget[parAddr[i]+parR] = random(256); // red
      dmxStateTarget[parAddr[i]+parG] = random(256); // green
      dmxStateTarget[parAddr[i]+parB] = random(256); // blue
    }
  }
  //**********************************************************************************
  if (strncmp("cyclerandom",(char*)payload, 11) == 0) {
    //message format: "cyclerandom <Light>"
    char *token;
    int light = 0;
    token = strtok((char*)payload, " ");  //first token is now "cyclerandom"
    token = strtok(NULL, " ");            //token is now the first value (Light)
    if (token != NULL) {
      light  = atoi(token);
      dmxStateTarget[parAddr[light]+parLum] = random(50,256);  //luminance
      dmxStateTarget[parAddr[light]+parR] = random(256); // red
      dmxStateTarget[parAddr[light]+parG] = random(256); // green
      dmxStateTarget[parAddr[light]+parB] = random(256); // blue
    }
  }
  //**********************************************************************************
  if (strncmp("rgbl",(char*)payload, 4) == 0) {
    //message format: "rgbl <Light> <R> <G> <B> <L>"
    char *token;
    int light;
    token = strtok((char*)payload, " ");  //first token is now "rgbl"
    token = strtok(NULL, " ");            //token is now the first value (Light)
    if (token != NULL) {
      light  = atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the second value (red)
    if (token != NULL) {
      dmxStateTarget[parAddr[light]+parR] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the third value (green)
    if (token != NULL) {
      dmxStateTarget[parAddr[light]+parG] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the fourth value (blue)
    if (token != NULL) {
      dmxStateTarget[parAddr[light]+parB] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the fifth value (luminance)
    if (token != NULL) {
      dmxStateTarget[parAddr[light]+parLum] = (byte)atoi(token);
    }
  }
  //**********************************************************************************
  if (strncmp("setchannel",(char*)payload, 10) == 0) {
    //message format: "setchannel <chan> <value>"
    char *token;
    byte channel=0;
    byte value=0;
    token = strtok((char*)payload, " ");  //first token is now "setchannel"
    token = strtok(NULL, " ");            //token is now the first value (channel)
    if (token != NULL) {
      channel = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the second value (value)
    if (token != NULL) {
      value = (byte)atoi(token);
    }
    dmxState[channel] = value;
    dmxStateTarget[channel] = value;
    dmxB.setChans(dmxState, 512);
  }
  //**********************************************************************************
  if (strncmp("fadespeed",(char*)payload, 9) == 0) {
    //message format: "fadespeed <speed (in miliseconds)>"
    // FIXME: restrict to sane values, e.g. 10 miliseconds seems to be too fast and yields weird effects!
    char *token;
    token = strtok((char*)payload, " ");  //first token is now "fadespeed"
    token = strtok(NULL, " ");            //token is now the first value (speed)
    if (token != NULL) {
      fadespeed = (unsigned int)atoi(token);
    }
  }
  //**********************************************************************************
  if (strncmp("discopanic",(char*)payload, 10) == 0) {
    memset(dmxState, 0x00, sizeof(dmxState));
    memset(dmxStateTarget, 0x00, sizeof(dmxStateTarget));
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxState[parAddr[i]+parFadeSpeed] = 230;
      dmxStateTarget[parAddr[i]+parFadeSpeed] = 230;
    }
    dmxB.setChans(dmxState, 512);
  }
  //**********************************************************************************
  if (strncmp("fadeRGB",(char*)payload, 7) == 0) {
    memset(dmxState, 0x00, sizeof(dmxState));
    memset(dmxStateTarget, 0x00, sizeof(dmxStateTarget));
    for (int i=0; i < NUM_LIGHTS; i++) {
      dmxState[parAddr[i]+parFadeSpeed] = 100;
      dmxStateTarget[parAddr[i]+parFadeSpeed] = 100;
    }
    dmxB.setChans(dmxState, 512);
  }
}


void loop() {
  httpServer.handleClient();
  webSocketServer.loop();

  if (!mqttClient.connected()) {
    mqtt_reconnect();
  }
  mqttClient.loop();

  now = millis();
  if (now - last >= fadespeed && memcmp(dmxState, dmxStateTarget, sizeof(dmxState)) != 0) {
    for (int i=0; i < 255; i++){
      if (dmxState[i] > dmxStateTarget[i]){
        dmxState[i]--;
      } else if (dmxState[i] < dmxStateTarget[i]){
        dmxState[i]++;
      }
    }
    dmxB.setChans(dmxState, 512);
    last = millis();
  }
}
