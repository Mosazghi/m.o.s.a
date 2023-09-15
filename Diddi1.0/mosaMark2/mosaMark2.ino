
#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

int pickUpSted = 0;
int dropSted = 0;
int position = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starter...");
  s2.attach(10); 
  s3.attach(11);
  s1.attach(9); 
  s4.attach(12);
  s5.attach(13);
  delay(200);
  RestPos();
}

void loop() {

  /*INPUT FRA BRUKER*/
if (Serial.available()){
  Serial.println("Rute er satt!");
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 

    if (input.startsWith("p-")){
      pickUpSted = input.substring(2).toInt();
      Serial.print("Hente sted satt til P-");
      Serial.println(pickUpSted);
    }
    else if (input.startsWith("d-")){
      dropSted = input.substring(2).toInt();
      Serial.print("Hente sted satt til D-");
      Serial.println(dropSted);
    }

    if(pickUpSted && dropSted){
      Serial.println("Rute er satt!");
      moveArm(pickUpSted, dropSted);
    }
  }
  // /*Input for test*/
  // if (Serial.available()){
  //   String input = Serial.readStringUntil('\n'); 
  //   input.trim(); 
    
  //   if (input.startsWith("s1-")){
  //     position = input.substring(3).toInt();
  //     //s1.write(position);
  //     SoftMove(s1, position);
  //     Serial.print("Servo 1 position set to ");
  //     Serial.println(position);
  //   } else if (input.startsWith("s2-")){
  //     position = input.substring(3).toInt();
  //     if(position <= 180){ // KAN FJERNE IF LØKKE ENDRE RANGE
  //       //s2.write(position);
  //       SoftMove(s2, position);
  //       Serial.print("Servo 2 position set to ");
  //       Serial.println(position);
  //     } else {
  //       Serial.println("UTENFOR RANGE!");
  //     }
  //   } else if(input.startsWith("s3-")){
  //     position = input.substring(3).toInt();
  //     if(position <= 180){
  //     //s3.write(position);
  //     SoftMove(s3, position);
  //     Serial.print("Servo 3 position set to ");
  //     Serial.println(position);     
  //     } else {
  //       Serial.println("UTENFOR RANGE!");
  //     }
  //   } else if(input.startsWith("s4-")){
  //     position = input.substring(3).toInt();
  //     s4.write(position);
  //     //SoftMove(s4, position);
  //     Serial.print("Servo 4 position set to ");
  //     Serial.println(position);     
  //   } else if(input.startsWith("s5-")){
  //     position = input.substring(3).toInt();
  //     //position = constrain(position, 0, 180); 
  //     s5.write(position);
  //     // SoftMove(s5, position);
  //     Serial.print("Servo 5 position set to ");
  //     Serial.println(position);     
  //   }
  // }
}

void moveArm(int pSted, int dSted){
  RestPos();
  if(pSted== 1 && dSted== 2){
    GoToPos1();
    delay(200);
    RestPos();
    GoToPos2();
    delay(200);
  } else if(pSted== 1 && dSted== 3){
    GoToPos1();
    delay(200);
    RestPos();
    GoToPos3();
    delay(200);
  } else if(pSted== 2 && dSted== 3){
    GoToPos2();
    delay(200);
    RestPos();
    GoToPos3();
    delay(200);
  }
  RestPos();
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

void GoToPos3(){
  SoftMove(s1, 180);
  SoftMove(s3, 120);
  SoftMove(s2, 40);
  SoftMove(s3, 90);
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
  delay(800);
}

void PickUp(){
  s4.write(60); 
  s5.write(140);
  delay(1000);
  s4.write(0); 
  s5.write(180);
  delay(800);
}
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