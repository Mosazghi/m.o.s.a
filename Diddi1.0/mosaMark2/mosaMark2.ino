#include "funksjonerArm.h"

int pickUpSted = 0;
int dropSted = 0;
int position = 0;

unsigned long prevMillis = 0;
const long interval = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("Starter...");
  delay(500); 
  s2.attach(10); 
  delay(500); 
  s3.attach(11);
  delay(500); 
  s1.attach(9);
  delay(500);  
  s4.attach(12);
  s5.attach(13);
  delay(500);  
  RestPos();
  Serial.println("Tast in pickup-sted (p'x') og drop-sted (d'x')");
}

void loop() {

  /*INPUT FRA BRUKER*/
if (Serial.available()){
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 

    if (input.startsWith("p")){
      pickUpSted = input.substring(1).toInt();
      Serial.print("Pickup-sted satt til P-");
      Serial.println(pickUpSted);
    }
    else if (input.startsWith("d")){
      dropSted = input.substring(1).toInt();

      Serial.print("Drop-sted satt til D-");
      Serial.println(dropSted);
    }

    if(pickUpSted && dropSted){
      moveArm(pickUpSted, dropSted);
      pickUpSted = 0;
      dropSted = 0;
      Serial.println("Utfører flytte-funksjon!");
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