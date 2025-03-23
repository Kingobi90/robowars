// My Robot Test Script

// Pin Definitions (match main sketch)
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

void setup() {
  Serial.begin(9600);
  
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

  Serial.println("Starting component tests...");
}

void loop() {
  // Test ultrasonic sensors
  testUltrasonic("Front", frontUS_trigger, frontUS_echo);
  testUltrasonic("Left", leftUS_trigger, leftUS_echo);
  testUltrasonic("Right", rightUS_trigger, rightUS_echo);

  // Test IR sensors
  testIRSensor("Left IR", irLeft);
  testIRSensor("Right IR", irRight);

  // Test motors
  testMotor(motor1, "Motor 1");
  testMotor(motor2, "Motor 2");
  testMotor(motor3, "Motor 3");
  testMotor(motor4, "Motor 4");

  delay(2000); // Wait before next test cycle
}

void testUltrasonic(const char* name, int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print(name);
  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void testIRSensor(const char* name, int pin) {
  int value = digitalRead(pin);
  Serial.print(name);
  Serial.print(" Value: ");
  Serial.println(value);
}

void testMotor(int pin, const char* name) {
  Serial.print("Testing ");
  Serial.println(name);
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
  delay(500);
}
