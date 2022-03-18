#include <Stepper.h>

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

void stepperTrigger(Stepper stepper,int count_steps){
  pressTrigger();
  if(trigger){
    stepper.step(count_steps);
    delay(500);
  }
}