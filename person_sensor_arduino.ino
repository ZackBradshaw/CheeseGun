#include <Wire.h>

#include "person_sensor.h"

#define RELAY_PIN 9
person_sensor_results_t results;

// How long to wait between reading the sensor. The sensor can be read as
// frequently as you like, but the results only change at about 5FPS, so
// waiting for 200ms is reasonable.
const int32_t SAMPLE_DELAY_MS = 200;

void setup() {
  // You need to make sure you call Wire.begin() in setup, or the I2C access
  // below will fail.
  Wire.begin();
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  Wire.begin();
}

void loop() {
  person_sensor_results_t results = {};
  // Perform a read action on the I2C address of the sensor to get the
  // current face information detected.
  if (!person_sensor_read(&results)) {
    Serial.println("No person sensor results found on the i2c bus");
    delay(SAMPLE_DELAY_MS);
    return;
  }
  
  // Check if any face detected meets the minimum confidence threshold
  bool faceDetected = false;
  for (int i = 0; i < results.num_faces; ++i) {
    if (results.faces[i].box_confidence >= PERSON_SENSOR_CONFIDENCE_THRESHOLD) {
      faceDetected = true;
      break;
    }
  }

  // Turn on relay if a face is detected, regardless of the confidence
  digitalWrite(RELAY_PIN, faceDetected ? HIGH : LOW);
  
  Serial.println("********");
  Serial.print(results.num_faces);
  Serial.println(" faces detected");
  for (int i = 0; i < results.num_faces; ++i) {
    const person_sensor_face_t* face = &results.faces[i];
    // Print all detected faces without considering the confidence or whether they are facing
    Serial.print("Face #");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(face->box_confidence);
    Serial.print(" confidence, Box(");
    Serial.print(face->box_left);
    Serial.print(", ");
    Serial.print(face->box_top);
    Serial.print("), (");
    Serial.print(face->box_right);
    Serial.print(", ");
    Serial.print(face->box_bottom);
    Serial.println(")");
  }
  delay(SAMPLE_DELAY_MS);
}
