# esp-mqtt-dmx

This project is providing a MQTT-to-DMX gateway via an ESP8266 in our Hackerspace.
We used Artnet before but that just spams our network too much so this shall create some MQTT messages which control generic light setups like "fade all to white" or "fade channel 1 to red"

The ESP subscribes to topic "/dmx/push" on our MQTT broker and expects commands which we will describe here.

status: DRAFT
