//If we don't find anything we recieve a -4 , -2, and 0

void clearBuffer() {
  Serial.print("b");
}


void getCoords() {
  Serial.print("a");
  while (!Serial.available()) {

  }
  state = Serial.parseInt();
  ch = Serial.read();



  while (!Serial.available()) {}
  state1 = Serial.parseInt();
  ch = Serial.read();


  while (!Serial.available()) {}
  state2 = Serial.parseInt();
  ch = Serial.read();

  while (!Serial.available()) {}
  burgDog = Serial.parseInt();
  ch = Serial.read();
  
  Serial.print(state);
  Serial.print(", ");
  Serial.print(state1);
  Serial.print(", ");
  Serial.print(state2);

}
