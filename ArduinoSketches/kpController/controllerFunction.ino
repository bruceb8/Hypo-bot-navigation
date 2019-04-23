
  
void kController() {
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    positionLeft = newLeft;
    positionRight = newRight;
    long error = (positionRight - positionLeft)/kp;
    //If master is faster than slave
    Serial.print(error);
    lSpeed = lSpeed + error;
    Serial.print("    ");
    Serial.println(lSpeed);
      if(lSpeed > 255) {
        lSpeed = 255;
      }else if(rSpeed < 200) {
         lSpeed = 200;
        }
      
   
  }

  m.setRightMotorSpeed(rSpeed);
  m.setLeftMotorSpeed(lSpeed);

/*
 * I might need to add something here to reset the encoder
 * counts once they exceed a certain amount.  Read in both values
 * subtract and write 0 in one encoder and the difference in the other
 */
  
  delay(50);
}
