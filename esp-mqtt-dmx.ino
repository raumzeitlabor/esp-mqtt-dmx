
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

// Starting Addresses of PAR-Lights and Strobes
const byte parAddr[2] = {10, 20};
const byte strobeAddr[1] = {1};

// Channels of PAR Lights as offset to starting address
const byte parLum = 0;
const byte parR = 1;
const byte parG = 2;
const byte parB = 3;

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


void setup() {
  Serial.begin(115200);
  setup_wifi();
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  webSocketServer.begin();
  webSocketServer.onEvent(webSocket_event);

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqtt_callback);

  dmxB.begin(4);
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

  if (strncmp("fadetoblack",(char*)payload, 11) == 0) {
    memset(dmxStateTarget, 0x00, sizeof(dmxStateTarget));
  }
  if (strncmp("fadetowhite",(char*)payload, 11) == 0) {
    dmxStateTarget[9] = 255;  //luminance
    dmxStateTarget[10] = 255; // red
    dmxStateTarget[11] = 255; // green
    dmxStateTarget[12] = 255; // blue
  }
  if (strncmp("cyclerandom",(char*)payload, 11) == 0) {
    dmxStateTarget[9] = 255;  //luminance
    dmxStateTarget[10] = random(256); // red
    dmxStateTarget[11] = random(256); // green
    dmxStateTarget[12] = random(256); // blue
  }
  if (strncmp("rgbl",(char*)payload, 4) == 0) {
    //message format: "rgbl 255 255 255 255"
    char *token;
    token = strtok((char*)payload, " ");  //first token is now "rgbl"
    token = strtok(NULL, " ");            //token is now the first value (red)
    if (token != NULL) {
      dmxStateTarget[10] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the second value (green)
    if (token != NULL) {
      dmxStateTarget[11] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the third value (blue)
    if (token != NULL) {
      dmxStateTarget[12] = (byte)atoi(token);
    }
    token = strtok(NULL, " ");            //token is now the fourth value (luminance)
    if (token != NULL) {
      dmxStateTarget[9] = (byte)atoi(token);
    }
  }
  if (strncmp("setchannel",(char*)payload, 4) == 0) {
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
  if (now - last >= 50) {
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
