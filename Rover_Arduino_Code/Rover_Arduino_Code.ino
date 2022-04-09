#include <DHT.h>
#include <Stepper.h>
#include <SoftwareSerial.h>

  //Temparature Pins
#define DHTPIN 13
#define DHTTYPE DHT22
  DHT dht(DHTPIN, DHTTYPE);

float t;
float h;

//Light Sensor pins
const int IRSensor = 12;
bool irsensor_mode = false;

//flashlight trigger
const int fl = 10;
bool fl_state = false;

//Stepper Motor Pins
//#define STEPS 100
const int STEPS = 100;
const int STEPS2 = 100;
bool trigger = false;
const int button = 10;
Stepper stepper1(STEPS, 9, 7, 8, 6);
Stepper stepper2(STEPS, 5, 3, 4, 2);

SoftwareSerial s_esp_cam(0, 1); // RX, TX


int previous = 0;
void setup() {
  delay(5000);
  // put your setup code here, to run once:
  Serial.begin(9600);
  s_esp_cam.begin(115200);

  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
  pinMode(button, INPUT);
  pinMode (IRSensor, INPUT);
  pinMode(fl, OUTPUT);
  digitalWrite(fl, LOW);
  dht.begin();


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  temperatureListener();
  if (s_esp_cam.available()) {
    char res = char(s_esp_cam.read());
    if (res == 'u') {
      stepperTrigger(stepper1, STEPS);
    }
    if (res == 'd') {
      stepperTrigger(stepper1, -STEPS);
    }
    if (res == 'l') {
      stepperTrigger(stepper2, STEPS);
    }
    if (res == 'r') {
      stepperTrigger(stepper2, -STEPS);
    }
    if (res == 'f') {
      flashLightTrigger();
    }
    //    Serial.write(s_esp_cam.read());
  }
  //  Serial.println(Serial2.readString());

}

void pressTrigger() {
  if (digitalRead(button) == HIGH) {
    trigger = trigger ? false : true;
    Serial.println("Button Pressed");
    delay(1000);
  }
}

void stepperListener(Stepper stepper, int count_steps) {
  pressTrigger();
  if (trigger) {
    stepperTrigger(stepper, count_steps);
  }
}

void stepperTrigger(Stepper stepper, int count_steps) {
  Serial.println("Stepping");
  stepper.step(count_steps);
  delay(500);
}

void temperatureListener() {
  int readData = dht.read(DHTPIN);
  t = dht.readTemperature();
  h = dht.readHumidity();

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  delay(200);
}

void lightSensorListener() {
  int statusSensor = digitalRead(IRSensor);

  if (statusSensor != 1) {
    irsensor_mode = true;
    Serial.println("light sensor not detects");
  } else {
    Serial.println("light sensor detects");
  }
  if (irsensor_mode) {
    stepperTrigger(stepper1, 500);
    irsensor_mode = false;
  }
}

void flashLightTrigger(){
  if(fl_state){
    digitalWrite(fl, LOW);
   } else {
    digitalWrite(fl, HIGH);
   }
   fl_state = !fl_state;
}
