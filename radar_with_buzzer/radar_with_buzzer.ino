#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 7;
const int servoPin = 6;

Servo myServo;
unsigned long previousMillis = 0;
const long buzzerDuration = 1000; // Duration of buzzer sound in milliseconds

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  detectObject(); // Function to detect objects
  
  // Slowly move the servo back and forth
  moveServoSlow();
}

void detectObject() {
  long duration, distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  // Check distance and activate buzzer if object is detected
  if (distance <= 20 && distance > 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= buzzerDuration) {
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      previousMillis = currentMillis;
    }
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }
}

void moveServoSlow() {
  // Slowly move the servo back and forth
  for (int pos = 0; pos <= 180; pos += 1) { // Move from 0 to 180 degrees
    myServo.write(pos);              // Tell servo to go to position in variable 'pos'
    delay(15);                       // Wait 15 ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // Move from 180 to 0 degrees
    myServo.write(pos);              // Tell servo to go to position in variable 'pos'
    delay(15);                       // Wait 15 ms for the servo to reach the position
  }
}

