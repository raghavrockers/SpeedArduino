#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial bluetooth(5,6);
int motorPin1 = 8; // pin 2 on L293D IC
int motorPin2 = 13; // pin 7 on L293D IC
int motorPin3 = 11; // pin 2 on L293D IC
int motorPin4 = 12; // pin 7 on L293D IC
int enA=9;
int enB=10;
int pwm=250;
char state;
int flag,x=250;
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
   Wire.begin(9); 
  Wire.onReceive(receiveEvent);
}
void loop() {
 if(x==0){
  pwm=0;
  Serial.print("x is ");
  Serial.println(x);}
  if(x==160){
  pwm=160;
  Serial.print("x is ");
  Serial.println(x);}
  if(x==250){
  pwm=250;
  Serial.print("x is ");
  Serial.println(x);}
 blmotor();
}

void blmotor(){
   if (bluetooth.available()) {
    state=bluetooth.read();
    Serial.println(state);
    flag = 0;
  }

  // if the state is '0' the DC motor will turn off
  if (state == '0') {
    digitalWrite(motorPin1, LOW); // set pin 2 on L293D low
    digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
    digitalWrite(motorPin3, LOW); // set pin 10 on L293D low
    digitalWrite(motorPin4, LOW); // set pin 15 on L293D low
    
    if (flag == 0) {
      Serial.println("Motor: off");
      flag = 1;
    }
  }
  // if the state is '1' the motor will turn right
  else if (state == '1') {
    digitalWrite(motorPin1, LOW); // set pin 2 on L293D low
    digitalWrite(motorPin2, HIGH); // set pin 7 on L293D high
    digitalWrite(motorPin3, HIGH); // set pin 10 on L293D low
    digitalWrite(motorPin4, LOW); // set pin 15 on L293D low
    analogWrite(enA,pwm);
    analogWrite(enB,pwm);
    if (flag == 0) {
      Serial.println("Motor: right");
      flag = 1;
    }
  }
  // if the state is '2' the motor will turn left
  else if (state == '2') {
    digitalWrite(motorPin1, HIGH); // set pin 2 on L293D high
    digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
    digitalWrite(motorPin3, LOW); // set pin 10 on L293D low
    digitalWrite(motorPin4, HIGH); // set pin 15 on L293D low
    analogWrite(enA,pwm);
    analogWrite(enB,pwm);
    if (flag == 0) {
      Serial.println("Motor: left");
      flag = 1;
    }
  }
  // if the state is '3' the motor will turn forward
  else if (state == '3') {
    digitalWrite(motorPin1, HIGH); // set pin 2 on L293D low
    digitalWrite(motorPin2, LOW); // set pin 7 on L293D high
    digitalWrite(motorPin3, HIGH); // set pin 10 on L293D low
    digitalWrite(motorPin4, LOW); // set pin 15 on L293D low
    analogWrite(enA,pwm);
    analogWrite(enB,pwm);
    if (flag == 0) {
      Serial.println("Motor: forward");
      flag = 1;
    }
  }
  // if the state is '4' the motor will turn backward
  else if (state == '4') {
    digitalWrite(motorPin1, LOW); // set pin 2 on L293D high
    digitalWrite(motorPin2, HIGH); // set pin 7 on L293D low
    digitalWrite(motorPin3, LOW); // set pin 2 on L293D low
    digitalWrite(motorPin4, HIGH); // set pin 7 on L293D low
    analogWrite(enA,pwm);
    analogWrite(enB,pwm);
    if (flag == 0) {
      Serial.println("Motor: backward");
      flag = 1;
    }
  }
}
void receiveEvent(int bytes) {
  x = Wire.read();   
}
