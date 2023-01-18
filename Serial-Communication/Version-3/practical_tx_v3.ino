#include "HX711.h"
HX711 scale;

// Button and LED pins
const int BUTTON_PIN = 4;
const int BUILTIN_LED_PIN = 13;

// Loadcell pins
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

// Motor driver for water pump pins
const int PWMA_PIN = 10;
const int AI2_PIN = 8;
const int AI1_PIN = 9;
const int STBY_PIN = 5;

// Manual (later setpoint setter) motor driver input via potentiometer
const int POTENTIOMETER_PIN = A0;

const int data_size = 50;
float strain[data_size];
unsigned int valve[data_size];

unsigned long time_start;
unsigned long time_now;
unsigned long time[data_size];

bool process_started = false;
bool process_finished = false;
int last_index;

void setup() {
  Serial.begin(57600);

  // ---Initalizing weight scale---
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2280.f);

  // ---Initalizing motor driver for water pump---
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(AI2_PIN, OUTPUT);
  pinMode(AI1_PIN, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);

  digitalWrite(STBY_PIN, HIGH);

  // Forward rotation
  digitalWrite(AI1_PIN, HIGH);
  digitalWrite(AI2_PIN, LOW);
  

  // ---Initalizing button related pins---
  pinMode(BUILTIN_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  digitalWrite(BUILTIN_LED_PIN, LOW);
}

void loop() {
  while (process_finished == true) {
    digitalWrite(BUILTIN_LED_PIN, LOW);
    delay(100);
    digitalWrite(BUILTIN_LED_PIN, HIGH);
    delay(100);
   }

  if (process_started == false) {  // Button must be pushed for the system to start
    while (digitalRead(BUTTON_PIN) == LOW) { } 
      while (digitalRead(BUTTON_PIN) == HIGH) { }
      scale.tare();
      process_started = true;
      digitalWrite(BUILTIN_LED_PIN, HIGH);
      time_start = millis();
  }

  last_index = 0;
  for (int i = 0; i < data_size; i++) {
    time[i] = millis() - time_start; 
    
    // ---Strain Process and Data Sample---
    while (scale.is_ready() == 0) { } // This introduces a delay of around 100 ms to get strain sample
    strain[i] = scale.get_units();

    // ---Valve Process and Data Sample---
    valve[i] = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 0, 255);
    analogWrite(PWMA_PIN, valve[i]);
    
    // This serves somewhat as an interupt which ceases data collection at the current point and begins transmission followed by cleanup
    last_index = i;
    if (digitalRead(BUTTON_PIN) == HIGH) {break;}
  }
  
  //Serial.println("Time Before Transmission");
  //Serial.println(millis());
  Serial.println("SD");
  for (int i = 0; i < last_index; i++) {
    Serial.println(strain[i]);
  }
  Serial.println("VD");
  for (int i = 0; i < last_index; i++) {
    Serial.println(valve[i]);
  }
  Serial.println("TD");
  for (int i = 0; i < last_index; i++) {
    Serial.println(time[i]);
  }
  //Serial.println("Time After Transmission");
  //Serial.println(millis());

  if (digitalRead(BUTTON_PIN) == HIGH) {  // Must hold the button down so that the system wraps up what it is doing and stops
    process_finished = true;
    Serial.println("OVER");
    digitalWrite(BUILTIN_LED_PIN, LOW);
    // Make sure to add the final states the system should take such as the water pump motor being given 0 voltage
  }

  Serial.println("END");
}