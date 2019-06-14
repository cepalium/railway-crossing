// --------------------------------
// Author: Tuan Nguyen
// Date created: 20190605
// --------------------------------
/*
 * 
 */

// include libraries
#include <Servo.h>


// define pins
#define irPin1       A0
#define irPin2       A1
#define irPin3       A3
#define irPin4       A4
#define motorPin     9
#define ledPin       13


// define states
#define NO_TRAIN          0
#define TRAIN_LO          1
#define TRAIN_LI          2
#define TRAIN_RO          3
#define TRAIN_RI          4
#define TRAIN_MIDDLE      5


// define motor value of gate open/close
#define GATE_OPEN       50
#define GATE_CLOSED     140


// initialize variables and servo motor
int state = NO_TRAIN;
bool LO, LI;
bool RO, RI;
Servo myservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  // pin modes
  pinMode(irPin1, INPUT);   // ir sensor 1 pin as input
  pinMode(irPin2, INPUT);   // ir sensor 2 pin as input
  pinMode(irPin3, INPUT);   // ir sensor 3 pin as input
  pinMode(irPin4, INPUT);   // ir sensor 4 pin as input
  myservo.attach(motorPin);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  // check train position
  int LO_value = analogRead(irPin1);
  int LI_value = analogRead(irPin2);
  int RI_value = analogRead(irPin3);
  int RO_value = analogRead(irPin4);
  
  LO = convertValue(LO_value);
  delay(5);
  LI = convertValue(LI_value);
  delay(5);
  RI = convertValue(RI_value);
  delay(5);
  RO = convertValue(RO_value);
  delay(5);
  
  state = updateState(state, LO, LI, RI, RO);
  controlGate(state);

  Serial.print(LO);
  Serial.print(" ");
  Serial.print(LI);
  Serial.print(" ");
  Serial.print(RI);
  Serial.print(" ");
  Serial.println(RO);
  Serial.println(state); // keep track of state
  Serial.println("-----------");
}


int convertValue(int value) {
// input: int value
// output: boolean
  if(value < 900) {
    return true;
    }  
  return false;
}

  
int updateState(int curState, bool leftOut, bool leftIn, bool rightIn, bool rightOut) {
// input: int curState, 4 booleans leftOut, leftIn, rightIn, rightOut 
// output: next state (logic based on state machine)
  
  if(curState==NO_TRAIN and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = NO_TRAIN;
    Serial.println(0);
    }
  if(curState==NO_TRAIN and leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LO;
    Serial.println(1);
    }
  if(curState==NO_TRAIN and !leftOut and !leftIn and !rightIn and rightOut) {
    curState = TRAIN_RO;
    Serial.println(2);
    }
  if(curState==TRAIN_LO and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = NO_TRAIN;
    Serial.println(3);
    }
  if(curState==TRAIN_LO and leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LO;
    Serial.println(4);
    }
  if(curState==TRAIN_LO and leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LI;
    Serial.println(5);
    }
  if(curState==TRAIN_LI and leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LO;
    Serial.println(6);
    }
  if(curState==TRAIN_LI and leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LI;
    Serial.println(7);
    }
  if(curState==TRAIN_LI and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_MIDDLE;
    Serial.println(8);
    }
  if(curState==TRAIN_RO and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = NO_TRAIN;
    Serial.println(9);
    }
  if(curState==TRAIN_RO and !leftOut and !leftIn and !rightIn and rightOut) {
    curState = TRAIN_RO;
    Serial.println(10);
    }
  if(curState==TRAIN_RO and !leftOut and !leftIn and rightIn) {
    curState = TRAIN_RI;
    Serial.println(11);
    }
  if(curState==TRAIN_RI and !leftOut and !leftIn and !rightIn and rightOut) {
    curState = TRAIN_RO;
    Serial.println(12);
    }
  if(curState==TRAIN_RI and !leftOut and !leftIn and rightIn) {
    curState = TRAIN_RI;
    Serial.println(13);
    }
  if(curState==TRAIN_RI and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_MIDDLE;
    Serial.println(14);
    }
  if(curState==TRAIN_MIDDLE and !leftOut and !leftIn and !rightIn and !rightOut) {
    curState = TRAIN_MIDDLE;
    Serial.println(15);
    }
  if(curState==TRAIN_MIDDLE and leftIn and !rightIn and !rightOut) {
    curState = TRAIN_LI;
    Serial.println(16);
    }
  if(curState==TRAIN_MIDDLE and !leftOut and !leftIn and rightIn) {
    curState = TRAIN_RI;
    Serial.println(17);
    }
    
  return curState;
}


void controlGate(int curState) {
// task: control the crossing gate and LED based on curState

  if((curState==NO_TRAIN) or (curState==TRAIN_LO) or (curState==TRAIN_RO)) { // train not crossing yet
    digitalWrite(ledPin, LOW);
    myservo.write(GATE_OPEN);
    Serial.println("OPEN");
    }
  else { // railway crossing
    digitalWrite(ledPin, HIGH);
    myservo.write(GATE_CLOSED);
    Serial.println("CLOSED");
    }
}
