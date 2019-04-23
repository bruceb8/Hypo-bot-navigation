//Code for the QRE1113 Digital board
//Outputs via the serial terminal – Lower numbers mean more reflected
//3000 or more means nothing was reflected.
int QRE1113_Pin = 7; //connected to digital 2

//OUR TWO PINS ARE 10 AND 7

void setup(){
  Serial.begin(9600);
}

void loop() {
  int QRE_Value = readQD();
  Serial.println(QRE_Value); 
}

int readQD(){
  pinMode(QRE1113_Pin,OUTPUT);
  digitalWrite(QRE1113_Pin, HIGH);
  delayMicroseconds(10);
  pinMode(QRE1113_Pin,INPUT);

  long time = micros();
  int diff = 0;
  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while(digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000){
    diff = micros() - time;
  }
  return diff;
  
}
