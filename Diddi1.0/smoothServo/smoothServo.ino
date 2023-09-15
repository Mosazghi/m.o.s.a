
#include <Servo.h>

Servo s1;

int position;

void setup() {
  
  Serial.begin(9600);
  s1.attach(9);
  
}

void loop() {
  if(Serial.available()){
    String input = Serial.readStringUntil('\n');
    input.trim();
    if(input.startsWith("s")){
      position = input.substring(1).toInt();
      position = constrain(position, 0, 180);
      SoftMove(s1,position);
      //s1.write(position);
    }
  }
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