#include <Wire.h>

#include "person_sensor.h"

#define RELAY_PIN 9
person_sensor_results_t results;

const int32_t SAMPLE_DELAY_MS = 2000;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  Wire.begin();
}

void loop() {
  person_sensor_results_t results = {};
  if (!person_sensor_read(&results)) {
    Serial.println("No person sensor results found on the i2c bus");
    return;
  }
  
  bool faceDetected = false;
  for (int i = 0; i < results.num_faces; ++i) {
    if (results.faces[i].box_confidence >= PERSON_SENSOR_CONFIDENCE_THRESHOLD) {
      faceDetected = true;
      break;
    }
  }

  if (faceDetected) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    delay(SAMPLE_DELAY_MS);
    digitalWrite(RELAY_PIN, LOW);
  }
  
  Serial.println("********");
  Serial.print(results.num_faces);
  Serial.println(" faces detected");
  for (int i = 0; i < results.num_faces; ++i) {
    const person_sensor_face_t* face = &results.faces[i];
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
}
