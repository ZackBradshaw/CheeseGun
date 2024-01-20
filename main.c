#include <Wire.h>
#include "person_sensor.h"

#define RELAY_PIN 8
person_sensor_results_t results;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Wire.begin();
}

void loop() {
  if (person_sensor_read(&results) && results.num_faces > 0) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }
  delay(1000);
}
