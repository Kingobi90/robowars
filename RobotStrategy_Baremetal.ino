// Robot Strategy - Search and Destroy (Baremetal)

// Port Definitions
#define FRONT_US_TRIGGER_PORT PORTD
#define FRONT_US_TRIGGER_DDR DDRD
#define FRONT_US_TRIGGER_PIN PD2

#define FRONT_US_ECHO_PIN PD3
#define LEFT_US_TRIGGER_PIN PD4
#define LEFT_US_ECHO_PIN PD5
#define RIGHT_US_TRIGGER_PIN PD6
#define RIGHT_US_ECHO_PIN PD7
#define IR_LEFT_PIN PB0
#define IR_RIGHT_PIN PB1
#define MOTOR1_PIN PB2
#define MOTOR2_PIN PB3
#define MOTOR3_PIN PB4
#define MOTOR4_PIN PB5

// Constants
const int DETECTION_DISTANCE = 20; // cm
const int PING_COUNT = 2;

// Variables
int frontDistance = 0;
int leftDistance = 0;
int rightDistance = 0;
int consecutivePings = 0;

// Add scanning variables
bool scanning = false;
uint8_t scanDirection = 0;

// Add edge detection variables
uint8_t edgeDetectionCount = 0;
const uint8_t EDGE_CONFIRMATION_COUNT = 3;

void setup() {
  // Configure pins
  FRONT_US_TRIGGER_DDR |= (1 << FRONT_US_TRIGGER_PIN);
  DDRD &= ~((1 << FRONT_US_ECHO_PIN) | (1 << LEFT_US_ECHO_PIN) | (1 << RIGHT_US_ECHO_PIN));
  DDRB |= (1 << MOTOR1_PIN) | (1 << MOTOR2_PIN) | (1 << MOTOR3_PIN) | (1 << MOTOR4_PIN);
  DDRB &= ~((1 << IR_LEFT_PIN) | (1 << IR_RIGHT_PIN));
}

void loop() {
  // Check ultrasonic sensors
  frontDistance = getDistance(FRONT_US_TRIGGER_PORT, FRONT_US_TRIGGER_PIN, FRONT_US_ECHO_PIN);
  leftDistance = getDistance(PORTD, LEFT_US_TRIGGER_PIN, LEFT_US_ECHO_PIN);
  rightDistance = getDistance(PORTD, RIGHT_US_TRIGGER_PIN, RIGHT_US_ECHO_PIN);

  // Check for opponent detection
  if (frontDistance <= DETECTION_DISTANCE || 
      leftDistance <= DETECTION_DISTANCE || 
      rightDistance <= DETECTION_DISTANCE) {
    consecutivePings++;
    if (consecutivePings >= PING_COUNT) {
      scanning = false;
      edgeDetectionCount = 0;
      attack();
    }
  } else {
    consecutivePings = 0;
    stopMotors();
    if (!scanning) {
      scanning = true;
      scanDirection = 0;
    }
    performScan();
  }

  // Enhanced edge detection
  if (!(PINB & (1 << IR_LEFT_PIN)) || !(PINB & (1 << IR_RIGHT_PIN))) {
    edgeDetectionCount++;
    if (edgeDetectionCount >= EDGE_CONFIRMATION_COUNT) {
      stopMotors();
      reverse();
      scanning = false;
      edgeDetectionCount = 0;
    }
  } else {
    edgeDetectionCount = 0;
  }
}

void performScan() {
  static uint32_t lastScanTime = 0;
  if (millis() - lastScanTime > 500) {
    lastScanTime = millis();
    if (scanDirection == 0) {
      // Turn left
      PORTB &= ~(1 << MOTOR1_PIN);
      PORTB |= (1 << MOTOR2_PIN);
      PORTB |= (1 << MOTOR3_PIN);
      PORTB &= ~(1 << MOTOR4_PIN);
      scanDirection = 1;
    } else {
      // Turn right
      PORTB |= (1 << MOTOR1_PIN);
      PORTB &= ~(1 << MOTOR2_PIN);
      PORTB &= ~(1 << MOTOR3_PIN);
      PORTB |= (1 << MOTOR4_PIN);
      scanDirection = 0;
    }
  }
}

int getDistance(volatile uint8_t &triggerPort, uint8_t triggerPin, uint8_t echoPin) {
  triggerPort &= ~(1 << triggerPin);
  _delay_us(2);
  triggerPort |= (1 << triggerPin);
  _delay_us(10);
  triggerPort &= ~(1 << triggerPin);

  uint32_t maxTime = 100000;
  uint32_t startTime = micros();
  while (!(PIND & (1 << echoPin)) && (micros() - startTime) < maxTime);
  startTime = micros();
  while ((PIND & (1 << echoPin)) && (micros() - startTime) < maxTime);
  return (micros() - startTime) * 0.034 / 2;
}

void attack() {
  PORTB |= (1 << MOTOR1_PIN) | (1 << MOTOR2_PIN) | (1 << MOTOR3_PIN) | (1 << MOTOR4_PIN);
}

void stopMotors() {
  PORTB &= ~((1 << MOTOR1_PIN) | (1 << MOTOR2_PIN) | (1 << MOTOR3_PIN) | (1 << MOTOR4_PIN));
}

void reverse() {
  // Implement reverse logic if needed
}
