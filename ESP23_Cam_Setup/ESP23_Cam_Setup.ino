#include <BluetoothSerial.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("Rover V1"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  // put your main code here, to run repeatedly:
  //  if (Serial.available()) {
  //    SerialBT.write(Serial.read());
  //  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
