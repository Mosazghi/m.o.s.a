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
  int FRONT_SENSOR = digitalRead(A1);
  int LEFT_SENSOR = digitalRead(A2);
  int RIGHT_SENSOR = digitalRead(A3);
  int MID_SENSOR = digitalRead(A4);
  int BACK_SENSOR = digitalRead(A5);

  int count = 0;

if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) {
    forward(); //FORWARD
    Serial.println("Fremover");
}

  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1) {
    right(); //Move Right
    Serial.println("Høyre");
 }

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0) {
    left(); //Move Left
    Serial.println("Venstre");
}

  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1) {
    Stop();  //STOP
    Serial.println("Stopper");
 }

 else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && MID_SENSOR==1 && FRONT_SENSOR==1 && BACK_SENSOR==1){   //Kryss
  intersection(); 
  Serial.println("Ved kryss");
 }

 else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1 && MID_SENSOR==0 && FRONT_SENSOR==1 && BACK_SENSOR==1)
  dropSpot();
  Serial.println("Ved drop spot");

}

void dropSpot(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void intersection(){

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