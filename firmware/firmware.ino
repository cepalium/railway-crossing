// --------------------------------
// Author: Tuan Nguyen
// Date created: 20190509
//
// Topic: Railway Crossing
// Tasks: 
// * read left & right sonar sensor
// * train approaching the gate -> close gate
// * train leaving the gate -> open gate
//
// Version reviewed:
// Version  | Date      | Jobs
// 1.1      | 20190514  | Factorize the code
// --------------------------------


// include libraries
#include <Servo.h>


// define pins
#define TRIGGER_LEFT    6  // trigger pin of left sonar
#define ECHO_LEFT       7  // echo pin of left sonar
#define TRIGGER_RIGHT   3   // trigger pin of right sonar
#define ECHO_RIGHT      4   // echo pin of right sonar
#define motorPin        9
#define ledPin          13


// define states
#define NO_TRAIN          0
#define TRAIN_IN_LEFT     1
#define TRAIN_IN_RIGHT    2
#define TRAIN_IN_MIDDLE   3
#define TRAIN_OUT_LEFT    4
#define TRAIN_OUT_RIGHT   5


// define motor value of gate open/close
#define GATE_OPEN       60
#define GATE_CLOSED     150


// initialize variables and servo motor
int state = NO_TRAIN;
bool L = false;
bool R = false;
Servo myservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(TRIGGER_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIGGER_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  myservo.attach(motorPin);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:

  // check if train is at any sensor
  L = isTrainLeft();
  R = isTrainRight();

  state = updateState(state, L, R);
  controlGate(state);
  
  Serial.println(state); // keep track of state
  Serial.println("-----------");
  delay(500);
}


bool isTrainLeft() {
// task: control sonar to measure distance
// output: return True if train is at left sonar, otw. false

  double duration, distance;
  digitalWrite(TRIGGER_LEFT, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER_LEFT, HIGH);
  delayMicroseconds(100); 
  
  digitalWrite(TRIGGER_LEFT, LOW);
  duration = pulseIn(ECHO_LEFT, HIGH);
  distance = (duration/2) / 31;
  
  Serial.print("lDistance:");
  Serial.println(distance);

  if(distance < 10) {
    return true;
  }
  return false;
}


bool isTrainRight() {
// task: control sonar to measure distance
// output: return True if train is at right sonar, otw. false

  double duration, distance;
  digitalWrite(TRIGGER_RIGHT, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER_RIGHT, HIGH);
  delayMicroseconds(100); 
  
  digitalWrite(TRIGGER_RIGHT, LOW);
  duration = pulseIn(ECHO_RIGHT, HIGH);
  distance = (duration/2) / 31;
  
  Serial.print("rDistance:");
  Serial.println(distance);

  if(distance < 10) {
    return true;
  }
  return false;
}


int updateState(int curState, bool leftSignal, bool rightSignal) {
// input: current state, value of left & right sonar sensors (logic based on state machine) 
// output: new current state
  
  if(curState==NO_TRAIN and !leftSignal and !rightSignal) {
    curState = NO_TRAIN;
    }
  if(curState==NO_TRAIN and leftSignal) {
    curState = TRAIN_IN_LEFT;
    }
  if(curState==NO_TRAIN and rightSignal) {
    curState = TRAIN_IN_RIGHT;
    }
  if(curState==TRAIN_IN_LEFT and leftSignal and !rightSignal) {
    curState = TRAIN_IN_LEFT;
    }
  if(curState==TRAIN_IN_RIGHT and !leftSignal and rightSignal) {
    curState = TRAIN_IN_RIGHT;
    }
  if((curState==TRAIN_IN_LEFT or state==TRAIN_IN_RIGHT or state==TRAIN_IN_MIDDLE) and !leftSignal and !rightSignal) {
    curState = TRAIN_IN_MIDDLE;
    }
  if(curState==TRAIN_IN_MIDDLE and !leftSignal and rightSignal) {
    curState = TRAIN_OUT_RIGHT;
    }
  if(curState==TRAIN_IN_MIDDLE and leftSignal and !rightSignal) {
    curState = TRAIN_OUT_LEFT;
    }
  if((curState==TRAIN_OUT_LEFT or curState==TRAIN_OUT_RIGHT) and !leftSignal and !rightSignal) {
    curState = NO_TRAIN;
    }

  return curState;
}


void controlGate(int curState) {
// task: control the crossing gate and LED

  if(curState==NO_TRAIN) { // no train
    digitalWrite(ledPin, LOW);
    myservo.write(GATE_OPEN);
    }
  else { // railway crossing
    digitalWrite(ledPin, HIGH);
    myservo.write(GATE_CLOSED);
    }
}
