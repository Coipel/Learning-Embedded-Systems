// This program is to be used simultaneously with the python serial_send.py

int strain[] = {1,21,37,47,21,34,33,575,231,234,665};
int valve[] = {0,22,34,244,665,234,231,575,33,34,11};
int data_size = 11;

int input;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0) {}
  input = Serial.read();
  Serial.println(input);

  if (input != 0) {
    if (input == 'A') {
      Serial.println("Arduino Transmitting...");
      Serial.println("Strain Data");
      for (int i = 0; i < data_size; i++){
        Serial.println(strain[i]);
      }
      
      Serial.println("Valve Data");
      for (int i = 0; i < data_size; i++){
        Serial.println(valve[i]);
      }

    }
    else {
      Serial.println("I don't hear a greeting");
    }
  }

  input = 0;
}
