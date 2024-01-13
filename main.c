#include <Wire.h>
#include "person_sensor.h"

#define RELAY_PIN 8
person_sensor_results_t results;

void setup() {
  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as output
  Wire.begin(); // Initialize the I2C bus
}

void loop() {
  if (person_sensor_read(&results) && results.num_faces > 0) {
    digitalWrite(RELAY_PIN, HIGH); // Turn the relay on
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn the relay off
  }
  delay(1000); // Wait for a second before the next read
}
