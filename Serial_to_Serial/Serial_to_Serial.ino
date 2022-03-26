#include <SoftwareSerial.h>

//SoftwareSerial s2(1, 3); // RX, TX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  s2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("t");
//  if(s2.available()>0){
//    s2.write("hellow");
//    Serial.println("writing hellow");
//  }
}
