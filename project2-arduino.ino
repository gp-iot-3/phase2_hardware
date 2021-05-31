#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 6);
float temp;
int tempPin = 1;
String str;

void setup() {
 Serial.begin(9600);
espSerial.begin(9600);
}
void loop() {
 temp = analogRead(tempPin);
 temp = temp * 0.48828125;
 Serial.print("TEMPERATURE = ");
 Serial.print(temp);
 Serial.print("*C");
 Serial.println();
 str =String(temp);
  espSerial.println(str);
 delay(5000);
}
