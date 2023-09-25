
#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

void SoftMove(Servo servo, int targetPos){
  int step = 0;
  int currentPos = servo.read();
  // Rotasjon mot klokka
  if(targetPos > currentPos){ 
    step = (targetPos - currentPos > 0) ? 1 : 0;
    for(int pos = currentPos; pos < targetPos; pos += step){
      servo.write(pos);
      delay(10);
    }
  } // Rotasjon med klokka
  else{
    step = (currentPos - targetPos > 0) ? 1 : 0;  
    for(int pos = currentPos; pos > targetPos; pos -= step){
      servo.write(pos);
      delay(10);
    }
  }
  servo.write(targetPos);
}

void GoToPos1(){
  SoftMove(s1, 0);
  SoftMove(s3, 90);
  SoftMove(s2, 20);
  delay(500);
}

void GoToPos2(){
  SoftMove(s1, 60);
  SoftMove(s2, 40);
  SoftMove(s3, 40);
  delay(200);
  SoftMove(s3, 130);
  SoftMove(s2, 0);
}

void OutFromPos3(){
  SoftMove(s2, 40);
  SoftMove(s3, 100);
  SoftMove(s2, 80);
  SoftMove(s3, 60);
}

void GoToPos3(){
  SoftMove(s1, 180);
  SoftMove(s3, 90);
  SoftMove(s2, 50);
  SoftMove(s3, 120);
  SoftMove(s2, 50);
  SoftMove(s3, 150);
  SoftMove(s2, 13);
  delay(800);
}

void RestPos(){
  SoftMove(s2, 130);
  SoftMove(s1, 60);
  delay(200);
  SoftMove(s3, 40);
  delay(200);
  s4.write(0); 
  s5.write(180);
  delay(800);
}

void DropIt(){
  s4.write(90);
  s5.write(90);
  delay(1000);
  int currentS2Pos = s2.read();
  SoftMove(s2, currentS2Pos+20);
  delay(200);
  s4.write(0);
  s5.write(180);
}

void PickUp(){
  s4.write(90);
  s5.write(90);
  delay(1000);
  s4.write(0);
  s5.write(180);
  delay(1000);
}


void moveArm(int pSted, int dSted){
  RestPos();
  if(pSted== 1 && dSted== 2){
    GoToPos1();
    delay(200);
    PickUp();
    delay(200);
    RestPos();
    GoToPos2();
    delay(200);
    DropIt();
    delay(200);
  } else if(pSted== 1 && dSted== 3){
    GoToPos1();
    delay(200);
    PickUp();
    delay(200);
    RestPos();
    GoToPos3();
    delay(200);
    DropIt();
    delay(200);
    OutFromPos3();

  } else if(pSted== 2 && dSted== 3){
    GoToPos2();
    delay(200);
    PickUp();
    delay(200);
    RestPos();
    GoToPos3();
    delay(200);
    DropIt();
    delay(200);
    OutFromPos3();
  } else if(pSted==2  && dSted== 1){
    GoToPos2();
    delay(200);
    PickUp();
    delay(200);
    RestPos();
    GoToPos1();
    delay(200);
    DropIt();
    delay(200);

  } else if(pSted==3  && dSted== 1){
    GoToPos3();
    delay(200);
    PickUp();
    delay(200);
    OutFromPos3();
    RestPos();
    GoToPos1();
    delay(200);
    DropIt();
    delay(200);
  } else if(pSted==3  && dSted== 2){
    GoToPos3();
    delay(200);
    PickUp();
    delay(200);
    OutFromPos3();
    RestPos();
    GoToPos2();
    delay(200);
    DropIt();
    delay(200);
  }
  RestPos();
}
