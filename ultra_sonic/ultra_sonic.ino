// Includes the Servo library
#include<SoftwareSerial.h>
#include <Servo.h>
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 4;
const int echoPin = 5;
int enA = 9;
int in1 = 11;
int in2 = 10;
int z1 = 0;
int z2 = 0;
int z3 = 0;
int target;
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
Servo steer;

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2;
  return distance;
}

void scan() {
  for (int i = 150; i > 110; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    z1 = distance + z1;
    Serial.print("z1 cm: ");
    Serial.print(distance);
    Serial.print(" angle: ");
    Serial.println(i);
  }
  z1 = z1 / 40;
  for (int i = 110; i > 70; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    z2 = distance + z2;
    Serial.print("z2 cm: ");
    Serial.print(distance);
    Serial.print(" angle: ");
    Serial.println(i);
  }
  z2 = z2 / 40;
  for (int i = 70; i > 30; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    z3 = distance + z3;
    Serial.print("z3 cm: ");
    Serial.print(distance);
    Serial.print(" angle: ");
    Serial.println(i);
  }
  z3 = z3 / 40;

  Serial.print("z1: ");
  Serial.print(z1);
  Serial.print(" z2: ");
  Serial.print(z2);
  Serial.print(" z3: ");
  Serial.println(z3);
}


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(12);
  steer.attach(13);
}
void loop() {

  if (calculateDistance() <= 5 * 2.54){
  digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 200);
    delay(2000);
    digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
  } else if (calculateDistance() <= 20 * 2.54) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      scan();
      myServo.write(90);
      target = max(z1, max(z2, z3));
      Serial.print(target);
      if (target == z3) {
        Serial.println(" z3 ");
        steer.write(130);
      } else if (target == z1) {
        Serial.println(" z1 ");
        steer.write(50);
      } else if (target == z2) {
        Serial.println(" z2 ");
        steer.write(90);
      }
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 200);
      delay(5000);
    } else {
      steer.write(90);
      myServo.write(90);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 200);
    }
  }


