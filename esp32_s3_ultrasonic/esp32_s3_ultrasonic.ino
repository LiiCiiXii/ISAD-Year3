// ESP32-S3 + HC-SR04 ultrasonic sensor example
// Wiring:
// - VCC  -> 5V
// - GND  -> GND
// - TRIG -> GPIO 5
// - ECHO -> GPIO 4 through a voltage divider or level shifter
//
// Important:
// HC-SR04 ECHO is often 5V. The ESP32-S3 GPIO is 3.3V only.
// Use a voltage divider or logic level shifter on the ECHO pin.

const int TRIG_PIN = 5;
const int ECHO_PIN = 4;

// Timeout in microseconds. About 4 meters max range.
const unsigned long ECHO_TIMEOUT_US = 30000;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  if (duration == 0) {
    return -1.0;
  }

  // Sound speed approximation: 343 m/s
  // Distance = (time * speed) / 2
  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.println();
  Serial.println("ESP32-S3 Ultrasonic Sensor Example");
  Serial.println("Reading distance in centimeters...");
}

void loop() {
  float distanceCm = readDistanceCm();

  if (distanceCm < 0) {
    Serial.println("No echo received");
  } else {
    Serial.print("Distance: ");
    Serial.print(distanceCm, 2);
    Serial.println(" cm");
  }

  delay(500);
}
