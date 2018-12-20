/*
TinyCar: Zefyr Scott and Chris Baker, 12/6/2018
This code was designed to drive a car made from a TI-RSLK
Maze Edition:
https://university.ti.com/en/faculty/ti-robotics-system-learning-kit/ti-robotics-system-learning-kit
The car drives down a track made from a black line about 1
cm wide, until it encounters a perpendicular finish line.
The bump switches included in the kit were not used.
*/

//========= Pins =========//

// Line sensor pins

const int line1Pin = 65;    //7.0
const int line2Pin = 48;    //7.1
const int line3Pin = 64;    //7.2
const int line4Pin = 47;    //7.3
const int line5Pin = 52;    //7.4
const int line6Pin = 68;    //7.5
const int line7Pin = 53;    //7.6
const int line8Pin = 69;    //7.7

const int ledOnPin = 61;    //5.3

// Motor board pins

const int leftSLPPin = 31;  //3.7
const int rightSLPPin = 11; //3.6

const int leftDIRPin = 14;  //1.7
const int rightDIRPin = 15; //1.6

const int leftPWMPin = 40;  //2.7
const int rightPWMPin = 39; //2.6

//========= Other globals =========//

// car control variables

int lspeed = 240;
int rspeed = 240;

float speedShift = 1;
float speedScale = .25;

// There are only 8 sensors but position 0 in array is not used for
// later code readability
int sensor[9] = {0};

//========= Setup =========//
// QTR-8RC module requires unusual setting of phototransistor pin modes
// in the loop rather than setup.

void setup() {

// Line sensor pins

  pinMode(ledOnPin, OUTPUT);
  digitalWrite(ledOnPin, 1);

// Motor board pins

  pinMode(leftSLPPin, OUTPUT);
  pinMode(rightSLPPin, OUTPUT);
  
  pinMode(leftDIRPin, OUTPUT);
  pinMode(rightDIRPin, OUTPUT);

  pinMode(leftPWMPin, OUTPUT);
  pinMode(rightPWMPin, OUTPUT);

//== Use for printout in testing ==// 
// Serial.begin(9600);

}

//========= Loop =========//

void loop() {

// Turn wheels on so they are ready to turn when they sense a line

  digitalWrite(leftDIRPin, 1);
  digitalWrite(leftSLPPin, 1);
//  analogWrite(leftPWMPin, lspeed);    
  
  digitalWrite(rightDIRPin, 1);
  digitalWrite(rightSLPPin, 1);
//  analogWrite(rightPWMPin, rspeed); 

// Set the phototransistors to output and to high
  pinMode(line1Pin, OUTPUT);
  pinMode(line2Pin, OUTPUT);
  pinMode(line3Pin, OUTPUT);
  pinMode(line4Pin, OUTPUT);
  pinMode(line5Pin, OUTPUT);
  pinMode(line6Pin, OUTPUT);
  pinMode(line7Pin, OUTPUT);
  pinMode(line8Pin, OUTPUT);
  digitalWrite(line1Pin,1);
  digitalWrite(line2Pin,1);
  digitalWrite(line3Pin,1);
  digitalWrite(line4Pin,1);
  digitalWrite(line5Pin,1);
  digitalWrite(line6Pin,1);
  digitalWrite(line7Pin,1);
  digitalWrite(line8Pin,1);

// Set the phototransistors to input and read them after a brief delay to 
// determine if the line is below.
  pinMode(line1Pin, INPUT);
  pinMode(line2Pin, INPUT);
  pinMode(line3Pin, INPUT);
  pinMode(line4Pin, INPUT);
  pinMode(line5Pin, INPUT);
  pinMode(line6Pin, INPUT);
  pinMode(line7Pin, INPUT);
  pinMode(line8Pin, INPUT);
  delay(1);
 
//== Use for printout in testing ==// 
//  Serial.print(digitalRead(line8Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line7Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line6Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line5Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line4Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line3Pin));
//  Serial.print(" ");
//  Serial.print(digitalRead(line2Pin));
//  Serial.print(" ");
//  Serial.println(digitalRead(line1Pin));
  
  sensor[1] = digitalRead(line1Pin);
  sensor[2] = digitalRead(line2Pin);
  sensor[3] = digitalRead(line3Pin);
  sensor[4] = digitalRead(line4Pin);
  sensor[5] = digitalRead(line5Pin);
  sensor[6] = digitalRead(line6Pin);
  sensor[7] = digitalRead(line7Pin);
  sensor[8] = digitalRead(line8Pin);

// Sensor fusion: go through the array of sensors and for all sensors that are
// high (indicating the line is read), get the average of their indices. IE if
// sensors 2 and 3 are high, get 2.5. Then subtract that result from 4.5
// (average of 4 and 5). This will give a result from -3.5 (car is all the way
// to the right and needs to turn left quickly) to 3.5 (same thing but to the
// left and needs to turn right). That result can be used to determine the car's
// next motion.
  
  float indexSum = 0;
  float numOfSensors = 0;
  float position = 0;

// First get values which will be used to get the average.
  
  for(int i = 1; i <= 8; i++){
    indexSum += i * sensor[i];
    numOfSensors += sensor[i];
  }

// Exception scenario: all the sensors came up 1/black. This means the car
// has arrived at the stopping line, so stop the car. 
  
  if(numOfSensors == 8){
    analogWrite(leftPWMPin, 0);    
    analogWrite(rightPWMPin, 0); 
    delay(5000);
  }

// Another exception scenario: all the sensors came up 0/white. This is either an
// erroneous bit of bad data or the car has gone off the track, but either way, 
// ignore it and skip the turn logic. As long as at least 1 sensor (but not all 8) is high, check
// for turn behavior.
  
  else if(numOfSensors != 0){

// At least one sensor is on, so okay to calculate the position (no division
// by zero error)
  
    position = 4.5 - indexSum / numOfSensors;

// If position is negative, car is too far right, so decrease the speed on the
// left wheel proportionately to turn left.
  
    if(position < 0){
      position = speedShift + speedScale * position;
      analogWrite(leftPWMPin, position * lspeed);
    }

// If result is positive, car is too far left, so decrease the speed on the
// right wheel proportionately to turn right.
  
    else if(position > 0){
      position = speedShift - speedScale * position;
      analogWrite(rightPWMPin, position * rspeed);
    }
    
// If result is zero car is in the right spot, so get the wheels to the same
// speed.
  
    else{
          analogWrite(leftPWMPin, lspeed); 
          analogWrite(rightPWMPin, rspeed); 
      }
    }

// Slight delay to go at this speed before next loop
delay(2);
}
