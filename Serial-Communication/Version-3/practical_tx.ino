const int BUTTON_PIN = 4;
const int BUILTIN_LED_PIN = 13;

const int data_size = 50;
unsigned int strain[data_size];
unsigned int valve[data_size];

unsigned long time_start;
unsigned long time_now;
unsigned long time[data_size];

bool process_started = false;
bool process_finished = false;
int last_index;

void setup() {
  Serial.begin(57600);

  // Initalizing button related pins
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
      process_started = true;
      digitalWrite(BUILTIN_LED_PIN, HIGH);
      time_start = millis();
  }

  last_index = 0;
  for (int i = 0; i < data_size; i++) {
    time[i] = millis() - time_start; 
    delay(100); // Simulated delays in code that controls system (manual or automatic) and the sensor delay
    strain[i] = random(0,1000);
    valve[i] = random(0,255);
    
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
}
