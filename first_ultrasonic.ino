#include "ultrasonic.h"

float distance_cm;
UltraSonic ultrasonic_sensor;

void setup() {
  ultrasonic_sensor.setPins(9,10);
  ultrasonic_sensor.setupPins();
  Serial.begin(9600);
}

void loop() {
  distance_cm = ultrasonic_sensor.takeDistance_cm();
  if (distance_cm > 3 && distance_cm < 400) {
    Serial.print("Distance (cm): ");
    Serial.println(distance_cm);
    delay(2);
  }
}
