//Distance Tracker test
//taken from https://www.instructables.com/id/How-to-Use-the-Sharp-IR-Sensor-GP2Y0A41SK0F-Arduin/
int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float readVal = analogRead(sensorPin);
  float volts = readVal;
  Serial.print("Analog Read: ");
  Serial.print(volts);
  volts = volts * 5 / 1024;
  Serial.print("    Voltage = ");
  Serial.print(volts);
//  float distance = 13 * pow(volts, -1)*2.54;

//http://qqtrading.com.my/infrared-proximity-sensor-10-80cm-sharp-gp2y0a21yk0f
//Conversion factor taken from link above.
  
  float distance = 4800/(readVal - 20);
  if(distance < 0 || distance > 100) {
    distance = 0;
  }
  Serial.print("    Distance = ");
  Serial.println(distance);
  
}
