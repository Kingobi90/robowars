// Robot Strategy - Search and Destroy

// Pin Definitions
const int frontUS_trigger = 2;
const int frontUS_echo = 3;
const int leftUS_trigger = 4;
const int leftUS_echo = 5;
const int rightUS_trigger = 6;
const int rightUS_echo = 7;
const int irLeft = 8;
const int irRight = 9;
const int motor1 = 10;
const int motor2 = 11;
const int motor3 = 12;
const int motor4 = 13;

// Constants
const int DETECTION_DISTANCE = 20; // cm
const int PING_COUNT = 2;

// Variables
int frontDistance = 0;
int leftDistance = 0;
int rightDistance = 0;
int consecutivePings = 0;

void setup() {
  // Initialize pins
  pinMode(frontUS_trigger, OUTPUT);
  pinMode(frontUS_echo, INPUT);
  pinMode(leftUS_trigger, OUTPUT);
  pinMode(leftUS_echo, INPUT);
  pinMode(rightUS_trigger, OUTPUT);
  pinMode(rightUS_echo, INPUT);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
}

void loop() {
  // Check ultrasonic sensors
  frontDistance = getDistance(frontUS_trigger, frontUS_echo);
  leftDistance = getDistance(leftUS_trigger, leftUS_echo);
  rightDistance = getDistance(rightUS_trigger, rightUS_echo);

  // Check for opponent detection
  if (frontDistance <= DETECTION_DISTANCE || 
      leftDistance <= DETECTION_DISTANCE || 
      rightDistance <= DETECTION_DISTANCE) {
    consecutivePings++;
    if (consecutivePings >= PING_COUNT) {
      attack();
    }
  } else {
    consecutivePings = 0;
    stopMotors();
  }

  // Check IR sensors for edge detection
  if (digitalRead(irLeft) == LOW || digitalRead(irRight) == LOW) {
    stopMotors();
    reverse();
  }
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void attack() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
}

void stopMotors() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

void reverse() {
  // Implement reverse logic if needed
}
