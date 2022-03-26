<<<<<<< Updated upstream
#include <Stepper.h>
#include <SoftwareSerial.h>
SoftwareSerial s_esp_cam(0,1); // RX, TX

//#define STEPS 100
const int STEPS = 200;
const int STEPS2 = 200;
bool trigger = false;
const int button = 10;
Stepper stepper1(STEPS, 9,7,8,6);
Stepper stepper2(STEPS,5,3,4,2);

int previous = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  s_esp_cam.begin(115200);

  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
  pinMode(button, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  pressTrigger();
  if(trigger){
//    Serial.println("Up");
//    stepper.step(STEPS);
//    pressTrigger();
//    delay(1000);
//    stepper2.step(STEPS2);
//    pressTrigger();
//  
//    Serial.println("Down");
//    stepper.step(-STEPS);
//    pressTrigger();
//    delay(1000);
//    stepper2.step(-STEPS2);
//    pressTrigger();

    Serial.println("Up");
    stepperTrigger(stepper1,STEPS);
    delay(1000);
//    stepperTrigger(stepper2,STEPS2);
  
    Serial.println("Down");
    stepperTrigger(stepper1,-STEPS);
    delay(1000);
//    stepperTrigger(stepper2,-STEPS2);
  }
  delay(500);
//  if(s_esp_cam.available() > 0){
//    Serial.println(s_esp_cam.read());
//  }
  if (s_esp_cam.available()) {
    char res = char(s_esp_cam.read());
    if(res == 't'){
      Serial.println("Test");
    }
//    Serial.write(s_esp_cam.read());
  }

}

void pressTrigger(){
  if(digitalRead(button) == HIGH){
    trigger = trigger ? false : true;
    Serial.println("Button Pressed");
    delay(1000);
  }
}

void stepperTrigger(Stepper stepper,int count_steps){
  pressTrigger();
  if(trigger){
    stepper.step(count_steps);
    delay(500);
  }
}
=======
#include <DHT.h>
#include <Stepper.h>

//Temparature Pins
#define DHTPIN 13
#define DHTTYPE DHT22 
DHT dht(DHTPIN,DHTTYPE);

float t;
float h;

//Light Sensor pins
const int IRSensor = 12;
bool irsensor_mode = false;

//Stepper Motor Pins
//#define STEPS 100
const int STEPS = 200;
const int STEPS2 = 200;
bool trigger = false;
const int button = 10;
Stepper stepper1(STEPS, 9,7,8,6);
Stepper stepper2(STEPS,5,3,4,2);

int previous = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial2.begin(115200);

  stepper1.setSpeed(60);
  stepper2.setSpeed(60);
  pinMode(button, INPUT);
  pinMode (IRSensor, INPUT);
  dht.begin();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  pressTrigger();
  if(trigger){
//    Serial.println("Up");
//    stepper.step(STEPS);
//    pressTrigger();
//    delay(1000);
//    stepper2.step(STEPS2);
//    pressTrigger();
//  
//    Serial.println("Down");
//    stepper.step(-STEPS);
//    pressTrigger();
//    delay(1000);
//    stepper2.step(-STEPS2);
//    pressTrigger();

    Serial.println("Up");
    stepperListener(stepper1,STEPS);
    delay(1000);
    stepperListener(stepper2,500);
  
    Serial.println("Down");
    stepperListener(stepper1,-STEPS);
    delay(1000);
    stepperListener(stepper2,-500);
  }
  lightSensorListener();
  temperatureListener();
  delay(200);

//  Serial.println(Serial2.readString());

}

void pressTrigger(){
  if(digitalRead(button) == HIGH){
    trigger = trigger ? false : true;
    Serial.println("Button Pressed");
    delay(1000);
  }
}

void stepperListener(Stepper stepper,int count_steps){
  pressTrigger();
  if(trigger){
    stepperTrigger(stepper,count_steps);
  }
}

void stepperTrigger(Stepper stepper,int count_steps){
  Serial.println("Stepping");
  stepper.step(count_steps);
  delay(500);
}

void temperatureListener(){
  int readData = dht.read(DHTPIN); 
  t = dht.readTemperature();
  h = dht.readHumidity();
  
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  delay(1000);
}

void lightSensorListener(){
  int statusSensor = digitalRead(IRSensor);
  
  if (statusSensor != 1){
    irsensor_mode = true;
    Serial.println("light sensor not detects");
  }else{
    Serial.println("light sensor detects");
  }
  if(irsensor_mode){
    stepperTrigger(stepper1,500);
    irsensor_mode = false;
  }
}
>>>>>>> Stashed changes
