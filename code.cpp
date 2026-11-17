#include <Servo.h>

// Pin definitions
const int moisturePin = A0;

const int relayPin = 6;
const int dryLedPin = 7;
const int wetLedPin = 8;
const int pumpLedPin = 9;
const int buzzerPin = 10;
const int servoPin = 5;

Servo pumpServo;

// Moisture threshold
// Lower value = dry soil in this simulation
const int moistureThreshold = 500;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(dryLedPin, OUTPUT);
  pinMode(wetLedPin, OUTPUT);
  pinMode(pumpLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pumpServo.attach(servoPin);

  Serial.begin(9600);

  // Initial state
  digitalWrite(relayPin, LOW);
  digitalWrite(dryLedPin, LOW);
  digitalWrite(wetLedPin, LOW);
  digitalWrite(pumpLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  pumpServo.write(0);
}

void loop() {

  // Read soil moisture
  int moistureValue = analogRead(moisturePin);

  Serial.print("Soil Moisture Value: ");
  Serial.println(moistureValue);

  // Check moisture level
  if (moistureValue < moistureThreshold) {

    // Soil is dry
    digitalWrite(dryLedPin, HIGH);
    digitalWrite(wetLedPin, LOW);

    // Turn ON pump
    digitalWrite(relayPin, HIGH);
    digitalWrite(pumpLedPin, HIGH);

    // Buzzer ON
    digitalWrite(buzzerPin, HIGH);

    // Move servo to represent pump activation
    pumpServo.write(90);

    Serial.println("STATUS: DRY - Irrigation ON");

  } 
  else {

    // Soil has enough moisture
    digitalWrite(dryLedPin, LOW);
    digitalWrite(wetLedPin, HIGH);

    // Turn OFF pump
    digitalWrite(relayPin, LOW);
    digitalWrite(pumpLedPin, LOW);

    // Buzzer OFF
    digitalWrite(buzzerPin, LOW);

    // Return servo
    pumpServo.write(0);

    Serial.println("STATUS: MOIST - Irrigation OFF");
  }

  delay(500);
}