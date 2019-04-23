


void actionsets() {
  //start in idle postion
  xArm.moveServos(6, 3000, 1, 700, 2, 500, 3, 300, 4, 500, 5, 500, 6, 125);


  //idle position for scanning the area (since the camera will be mounted on the arm)
  int pos1[6] = {500, 500, 300, 500, 500, 125};
  for (int i = 0; i < 6; i++ ) {
    idle[i].ID = i + 1;
    idle[i].Position = pos1[i];
  }


  /*
    //postition for safe intermidiate point after retreval before disposal
    int pos3[6] = {700, 100, 100, 120, 700, 500};
    for (int i = 0; i < 6; i++ ) {
      PostGrab[i].ID = i + 1;
      PostGrab[i].Position = pos3[i];
    }
  */

  int pos3[6] = {700, 500, 500, 500, 500, 500};
  for (int i = 0; i < 6; i++ ) {
    PostGrab[i].ID = i + 1;
    PostGrab[i].Position = pos3[i];
  }

  int pos7[6] = {700, 500, 500, 500, 500, 875};
  for (int i = 0; i < 6; i++ ) {
    PostGrabTurn[i].ID = i + 1;
    PostGrabTurn[i].Position = pos3[i];
  }

  //position holding target above disposal bin
  int pos4[6] = {700, 125, 90, 100, 650, 875};
  for (int i = 0; i < 6; i++ ) {
    OverBin[i].ID = i + 1;
    OverBin[i].Position = pos4[i];
  }

  //position releasing target and dropping into disposal bin
  int pos5[6] = {500, 125, 90, 100, 650, 875};
  for (int i = 0; i < 6; i++ ) {
    Drop[i].ID = i + 1;
    Drop[i].Position = pos5[i];
  }

  int pos6[6] = {500, 500, 300, 500, 500, 500};
  for (int i = 0; i < 6; i++ ) {
    lookAhead[i].ID = i + 1;
    lookAhead[i].Position = pos1[i];
  }

  delay(3000);
}

void FaceForward() {
  xArm.moveServos(1, 1000, 6, 500);
}

void GIT(float X, int angle) {
  float T3, T2, T1;



  T3 = theta3(X);
  T2 = theta2(X, T3);
  T1 = Rad2Units(theta1(T2, T3));

  T2 = Rad2Units(T2 + (2 * T3 - PI));
  T3 = Rad2Units(PI - T3);

/*
  xArm.moveServos(idle, 6, 3000);
  delay(3000);
*/
  int theta3 = (int) T3;
  int theta2 = (int) T2;
  int theta1 = (int) T1;

  //about to grab
  xArm.moveServos(6, 3000, 1, 300, 2, 500, 3, theta1, 4, theta2, 5, theta3, 6, 500);
  delay(3000);

  if (angle == 0) {
    //rotate claw
    xArm.moveServos(1, 1000, 2, 125);
    delay(1000);
  }

  //close claw
  xArm.moveServos(1, 500, 1, 700);
  delay(500);


  xArm.moveServos(PostGrab, 6, 3000);
  delay(3000);
/*
  xArm.moveServos(PostGrabTurn, 6, 3000);
  delay(3000);
*/
  xArm.moveServos(1, 1000, 6, 875);
  delay(1000);
  
  xArm.moveServos(OverBin, 6, 3000);
  delay(3000);

  xArm.moveServos(Drop, 6, 300);
  delay(300);

  xArm.moveServos(idle, 6, 3000);
  delay(3000);

}

int Rad2Units(float theta) { //converts radians to arm units
  return 500 - (2 * (theta / PI) * 375);
}

float theta3(float x) { //calculates the change in angle theta3 needed to reach x
  float a, b, r, k, alpha;
  a = c - y;
  b = x;
  r = sqrt(sq(a) + sq(b));
  alpha = atan(b / a);
  k = (sq(x) + sq(y) + sq(c) - 2 * c * y) / (2 * d);
  return (acos(k / r) + alpha);
}

float theta2(float x, float theta3) { //calculates the change in angle theta2 needed to reach x
  return acos((x / d) - sin(theta3)) - theta3 + (PI / 2);
}

float theta1(float theta2, float theta3) { //calculates the change in angle theta1 needed to reach x
  return PI - theta2 - theta3;
}
