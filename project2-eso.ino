#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

const char* ssid = "ScrumMaster";
const char* password = "12345678";
const char* mqtt_server = "broker.hivemq.com";
String temp_str;
char temp[50];


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message recive from  ");
  Serial.print(topic);
  Serial.print(" is : ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("iot-group2-project2", "we are connect");
      client.subscribe("iot-group2-project2");
    } else {
      Serial.print("khata dar ertebat ba server !!! ");
      Serial.print(client.state());
      delay(3000);
    }
  }
}


void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("etesal be modem : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Can not resolve the host :-(");
  }

  Serial.println("");
  Serial.println("WiFi connected :-)");
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println();

}


void loop() {
  if (Serial.available()) {
 if (!client.connected()) {
    reconnect();
  }
  client.loop();
    temp_str = Serial.readString();
    Serial.println(temp_str);
    temp_str.toCharArray(temp, temp_str.length() + 1);
    client.publish("iot-group2-project2", temp); //money shot
}
}
