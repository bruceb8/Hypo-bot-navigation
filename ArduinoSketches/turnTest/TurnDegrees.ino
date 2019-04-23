void rightTurnDegrees(int deg){
  //First we convert that into encoder ticks
  long target = deg * 30; //This constant value is a  ratio between degrees and encoder ticks

  //second stop the motors and add a small delay to stop the
  //encoder count
  m.allStop();
  delay(200);
  //third we zero out the encoders with enc.write(0)
  knobLeft.write(0);
  knobRight.write(0);
  //fourth we change the speed to the slow turn
  m.setRightMotorSpeed(230);
  m.setLeftMotorSpeed(230);
  //then we start the turn;
  m.turnRight();
  int currentLeft = knobLeft.read();
  int currentRight = knobRight.read();
  while(currentLeft < target || currentRight < target){
    currentRight = abs(knobRight.read());
    currentLeft = abs(knobLeft.read());
    Serial.println(currentRight);
  }
    m.allStop();
  delay(200);
}
