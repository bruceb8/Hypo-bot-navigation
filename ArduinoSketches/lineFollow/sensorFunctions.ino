int readLine(int QRE1113_Pin){
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
