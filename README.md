# esp-mqtt-dmx

This project is providing a MQTT-to-DMX gateway via an ESP8266 in our Hackerspace.
We used Artnet before but that just spams our network too much so this shall create some MQTT messages which control generic light setups like "fade all to white" or "fade Lamp 1 to red"

The ESP subscribes to topic "/dmx/push" on our MQTT broker and expects commands which we will describe here.

status: DRAFT

License: GPLv3

## MQTT-Commands

supported format of commands to be published to the "/dmx/push" topic:

|command|parameters|description|
|-------|----------|-----------|
|fadespeed|speed in miliseconds|this value is used as a "step width" to move from current DMX state to desired DMX state. Default value = 20, values below 20 seem to produce weird effects!|
|fadealltoblack|none|set all desired rgbl values for all light to 0 and fade towards that (darkness)|
|fadealltowhite|none|set all desired rgbl values for all light to 255 and fade towards that ("white")|
|fadealltored|none|set all desired rgbl values for all light to fade towards red|
|fadealltogreen|none|set all desired rgbl values for all light to fade towards green|
|fadealltoblue|none|set all desired rgbl values for all light to fade towards blue|
|cycleallrandom|none|set a random value for all rgbl values for all lights and fade towards that value|
|cyclerandom|light|set a specific light to random rgbl values and fade towards them (index starts at 0)|
|rgbl|light R G B L|set a specific light to specific values for R G B L (values 0-255)|
|setchannel|channel value|set a specific DMX channel to one specific value (without fading, hard set)|
|discopanic|none|set all lights to a random color strobe (using a special DMX channel/value pair)|
|fadeRGB|none|set all lights to go through a slow cycle of colors (using a special DMX channel/value pair)|

## Compiler config

We use an ESP-12E Module with 4M Flash-Size and 3M SPIFFS. This is important for in order to be able to do Web-OTA Updates we need the 3M SPIFFS to fit two versions of the Firmware into memory. Using 4M-1M Split will crash the controller during OTA. If using Arduino-IDE set Board to "NodeMCU 1.0 (ESP-12E Module)" and Flash to "4M (3M SPIFFS)"

At the time of writing (02/2019) the Arduino-Board-Version v4.2 seems to work well.

## OTA

compile with Arduino ide and upload via curl because we don't use mdns announce:

    curl -F "image=@esp-mqtt-dmx.ino.nodemcu.bin" http://172.22.37.112/update

## Websocket-Server

we run a websocket server on port 81 which prints some messages for debugging (because we're lazy and don't want to use the UART all the time).

## Credits

The main libraries/sources of code are:
  - espDMX written by Matt (@mtongnz), https://github.com/mtongnz/espDMX
  - esp ArtnetNode by Matt (@mtongnz), https://github.com/mtongnz/ESP8266_ArtNetNode_DMX
  - ESP8266 core for Arduino, https://github.com/esp8266/Arduino
