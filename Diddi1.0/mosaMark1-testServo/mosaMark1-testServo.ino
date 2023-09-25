#include <Servo.h>

/* 
  Spenning: 5V
   Strøm: 1 A
*/

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

unsigned long previousMillis = 0;
const long interval = 10; // Tidsintervall for hvert servosteg (juster etter behov)

int position;

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

  Serial.println("Rest posisjon");
  RestPos();
  delay(500);
}


void loop() {

  RestPos();
  delay(200);
  TurnToDrop();
  delay(200);
  RestPos();
  delay(200);
  
  // /*Plukk og dropp fuksjon*/
  // Serial.println("Plukke-funksjonen");
  // ArmDown();
  // delay(800);
  // PickUp();
  // ArmUp();
  // Serial.println("Slutt prosess");
  // Serial.println("Venter...");
  // delay(200);
  // Serial.println("Drop-funksjonen");
  // TurnToDrop();
  // DropIt();
  // ArmUp();
  // RestPos();
  // Serial.println("Utført drop funksjoner");
  // delay(800);

  // Input fra bruker
  if (Serial.available()){
    String input = Serial.readStringUntil('\n'); 
    input.trim(); 
    
    if (input.startsWith("s1-")){
      position = input.substring(3).toInt();
      //s1.write(position);
      SoftMove(s1, position);
      Serial.print("Servo 1 position set to ");
      Serial.println(position);
    } else if (input.startsWith("s2-")){
      position = input.substring(3).toInt();
      if(position <= 180){ // KAN FJERNE IF LØKKE ENDRE RANGE
        //s2.write(position);
        SoftMove(s2, position);
        Serial.print("Servo 2 position set to ");
        Serial.println(position);
      } else {
        Serial.println("UTENFOR RANGE!");
      }
    } else if(input.startsWith("s3-")){
      position = input.substring(3).toInt();
      if(position <= 180){
      //s3.write(position);
      SoftMove(s3, position);
      Serial.print("Servo 3 position set to ");
      Serial.println(position);     
      } else {
        Serial.println("UTENFOR RANGE!");
      }
    } else if(input.startsWith("s4-")){
      position = input.substring(3).toInt();
      s4.write(position);
      //SoftMove(s4, position);
      Serial.print("Servo 4 position set to ");
      Serial.println(position);     
    } else if(input.startsWith("s5-")){
      position = input.substring(3).toInt();
      //position = constrain(position, 0, 180); 
      s5.write(position);
      // SoftMove(s5, position);
      Serial.print("Servo 5 position set to ");
      Serial.println(position);     
    }
  }
}

void SoftMove(Servo servo, int targetPos) {
  int currentPos = servo.read();
  if (currentPos != targetPos) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      int step = (targetPos > currentPos) ? 1 : 0;
      int newPos = currentPos + step;
      servo.write(newPos);
    }
  }
}


void TurnToDrop(){
  SoftMove(s1, 180);
  SoftMove(s3, 120);
  SoftMove(s2, 40);
  SoftMove(s3, 90);
  delay(800);
  
  // s1.write(180);
  // s3.write(120);
  // s2.write(40);
  // s3.write(90);
  // delay(800);
}


void RestPos(){
  // SoftMove(s1, 60);
  // SoftMove(s2, 130);
  // delay(200);
  // SoftMove(s3, 40);
  // delay(200);
  // s4.write(0); 
  // s5.write(180);
  // delay(800);

  // s1.write(60);
  // s2.write(130);
  // delay(200);
  // s3.write(40);
  // delay(200);
  // s4.write(0); 
  // s5.write(180);
  // delay(800);
}

void ArmUp(){
  SoftMove(s2, 120);
  SoftMove(s3, 80);
  delay(200);
}

void ArmDown(){
  SoftMove(s2, 40);
  SoftMove(s3, 40);
  delay(200);
  SoftMove(s3, 130);
  SoftMove(s2, 0);
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

// void SoftMove(Servo servo, int targetPos){
//   int step = 0;
//   int currentPos = servo.read();
//   // Rotasjon mot klokka
//   if(targetPos > currentPos){ 
//     step = (targetPos - currentPos > 0) ? 1 : 0;
//     for(int pos = currentPos; pos < targetPos; pos += step){
//       servo.write(pos);
//       delay(10);
//     }
//   } // Rotasjon med klokka
//   else{
//     step = (currentPos - targetPos > 0) ? 1 : 0;  
//     for(int pos = currentPos; pos > targetPos; pos -= step){
//       servo.write(pos);
//       delay(10);
//     }
//   }
//   servo.write(targetPos);
// }
