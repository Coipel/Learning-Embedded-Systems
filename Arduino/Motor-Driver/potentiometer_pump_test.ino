const int PWMA_PIN = 10;
const int AI2_PIN = 8;
const int AI1_PIN = 9;
const int STBY_PIN = 2;

const int POTENTIOMETER_PIN = A0;

void setup() {
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(AI2_PIN, OUTPUT);
  pinMode(AI1_PIN, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);

  digitalWrite(STBY_PIN, HIGH);

  // Forward rotation
  digitalWrite(AI1_PIN, HIGH);
  digitalWrite(AI2_PIN, LOW);
}

void loop() {
  int raw_input = analogRead(POTENTIOMETER_PIN);
  int pump_input = map(raw_input, 0, 700, 0, 255); // [NOTE] Using 3.3 V on the potentiometer rather than 5 V so max value around 700 not 1023.
  Serial.println(pump_input);

  analogWrite(PWMA_PIN, pump_input);
}
