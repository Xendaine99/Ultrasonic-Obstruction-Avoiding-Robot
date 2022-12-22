#include<AFMotor.h>
// #include<NewPing.h>
#include<Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200 
#define MAX_SPEED 250
#define MAX_SPEED_OFFSET 20

// NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo; 
float dist = 0; 
long duration ; 
int speedSet = 0; 

void setup() {
  motor1.setSpeed(150); 
  motor2.setSpeed(150); 
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 
  Serial.begin(9600); 
  myservo.attach(10); 
  myservo.write(90); 
  dist = readDist(); 
  Serial.print("Inital distance: "); 
  Serial.print(dist); 
  Serial.println(" cm");  
}

void loop() {
  // put your main code here, to run repeatedly:
  float distR = 0;
  float distL = 0; 
  dist = readDist(); 
  Serial.print(dist); 
  Serial.println(" cm"); 
  
  if(dist <= 15){
    movestop();
     moveBackward(); 
    delay(500); 
    
    lookRight(); 
    distR = readDist(); 
    delay(50); 
     lookLeft(); 
     distL = readDist(); 
    if(distR > distL){
      turnRight();
      lookAhead(); 
      delay(50);  
      moveForward(); 
    }
    else if(distR < distL){
      turnLeft(); 
      lookAhead(); 
      delay(50); 
      moveForward(); 
    }
     
  }
  else{
    moveForward(); 
  }

}

void movestop(){
  motor1.run(RELEASE); 
  motor2.run(RELEASE); 
}


void lookAhead(){
  delay(50); 
  myservo.write(90); 
}

void lookRight(){
  myservo.write(0);
}

void lookLeft(){
myservo.write(180); 
}

float readDist(){
  digitalWrite(TRIG_PIN, LOW); 
  delay(2); 
  digitalWrite(TRIG_PIN, HIGH); 
  delay(10); 
  duration = pulseIn(ECHO_PIN, HIGH); 
   
  return (duration * 0.034)/ 2; 
}

void moveForward(){
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD); 
  for(speedSet = 0;speedSet<MAX_SPEED; speedSet+=2 ){
    motor1.setSpeed(speedSet); 
    motor2.setSpeed(speedSet); 
    delay(5); 
  }
}

void moveBackward(){
  motor1.setSpeed(150); 
  motor2.setSpeed(150); 
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD); 

}

void turnRight(){
  motor1.setSpeed(250); 
  motor2.setSpeed(250); 
  motor1.run(BACKWARD); 
  motor2.run(FORWARD); 
  delay(500); 
}

void turnLeft(){
  motor1.setSpeed(250); 
  motor2.setSpeed(250); 
  motor1.run(FORWARD); 
  motor2.run(BACKWARD); 
delay(500);
}
