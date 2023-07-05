/*
Code Name: Arduino Line Follower Robot Car
Code URI: https://circuitbest.com/category/arduino-projects/
Author: Make DIY
Author URI: https://circuitbest.com/author/admin/
Description: This program is used to make Arduino Line Follower Robot Car.
Note: You can use any value between 0 to 255 for M1_Speed, M2_Speed, LeftRotationSpeed, RightRotationSpeed.
Here 0 means Low Speed and 255 is for High Speed.
Version: 1.0
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/

#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5


 int M1_Speed = 80; // speed of motor 1
 int M2_Speed = 80; // speed of motor 2
 int LeftRotationSpeed = 250;  // Left Rotation Speed
 int RightRotationSpeed = 250; // Right Rotation Speed

 unsigned lineCount = 0;


 void setup() {
  Serial.begin(9600);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);

      pinMode(A1, INPUT);
      pinMode(A2, INPUT); // initialize Left sensor as an input
      pinMode(A3, INPUT); // initialize Right sensor as an input
      pinMode(A4, INPUT);
      pinMode(A5, INPUT);


}

void loop() {
  int FRONT_SENSOR = digitalRead(A0);
  int MID_SENSOR = digitalRead(A1); // Ikke i bruk 
  int LEFT_SENSOR = digitalRead(A2);
  int RIGHT_SENSOR = digitalRead(A3);
  int BACK_SENSOR = digitalRead(A4);

if(RIGHT_SENSOR==0 && LEFT_SENSOR==0 && BACK_SENSOR==1 && FRONT_SENSOR==1) {
    forward(); //FORWARD
    Serial.println("Fremover");
}

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1  && BACK_SENSOR==1 && FRONT_SENSOR==1) {
    right(); //Move Right
    Serial.println("Høyre");
 }

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0 && BACK_SENSOR==1 && FRONT_SENSOR==1) {
    left(); //Move Left
    Serial.println("Venstre");
}

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==0) {
    Stop();  //STOP
    Serial.println("Stopper");
 } 

 else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && BACK_SENSOR==1 && FRONT_SENSOR==1){   //Kryss
  int stajsonNr = 2; //Hardkodet 
  intersectionDetected();
  Serial.println("Ved krysset: ");
  Serial.print(lineCount);
  Serial.println(" ");
  if(lineCount == stajsonNr){
    Serial.println("Tar svingen til stasjon 2");
  }
  else
    forward();
 } 
}
//Ikke ferdig
void dropSpot(){
  Stop();
  delay(2000);
  turn();
  forward();
}


void intersectionDetected(){
  static long lastDetected = 0;
  if(millis() - lastDetected < 2000){ 
    return;
  }
  lastDetected = millis(); //Sist sjekket linje */
  lineCount++;
} 

void turn(){
  left();
  delay(2000);
}

void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}