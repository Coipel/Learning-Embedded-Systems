int array[] = {1,21,37,47};

void setup() {
  Serial.begin(9600);
}

void loop() {
  // [TODO] I need to stop ending data when an ACK is received and to only start collecting and sending data after a button is pushed
  Serial.println("Arduino Transmitting...");
  Serial.println("Strain Data");
  Serial.println("Size: 4");
  for (int i = 0; i < 4; i++){
    Serial.println(array[i]);
  }
}
