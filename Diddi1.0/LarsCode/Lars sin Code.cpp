#include "test.h"
#include "test2.h"

String input;



void GuessRandomVal(String a);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting");     

}

void loop() {
  // put your main code here, to run repeatedly
  if( Serial.available()){
    input = Serial.readStringUntil('\n');
    input.trim();
    if(input.startsWith("d")){
      //RESET FUNCTIONS
      RV.ValueInput = 1;
      RV.Command = input;
      //RESET FUNCTIONS
      ChooseLocation(input);
    }
    if(input.startsWith("g")){
      //RESET FUNCTIONS
      RV.ValueInput = 2;
      RV.Command = input;
      //RESET FUNCTIONS
      GuessRandomVal(input);
    }
    Serial.println("\nProgram has finished\n\n");
  }
}





void ResetFunction(String a){
  if(a == "r"){
    switch(RV.ValueInput){
      case 1 : ChooseLocation(RV.Command);
      case 2 : GuessRandomVal(RV.Command);
    }
  }
}



// .h num1
int n1(String a){ 
  int NUM = a.substring(1).toInt();
  return NUM;
} 


int splitString(String input, char delimiter, String output[]){
  int partCount = 0;
  int start = 0;
  for (int i = 0; i < input.length(); i++) {
    if (input.charAt(i) == delimiter) {
      output[partCount++] = input.substring(start, i);
      start = i + 1;
    }
  }
  output[partCount++] = input.substring(start);
  return partCount;
}


void ChooseLocation(String a){
  //PROGRAM
  Serial.println(a);
  if(a.startsWith("p")){
    String parts[2];
    Serial.println("Wallah");
    int SplitedString = splitString(a, ' ', parts);
    for( int i = 0; i < SplitedString; i++){
      if(parts[i].startsWith("p")){
        int pValue = parts[i].substring(1).toInt();
        Serial.println(pValue);
      }
      if(parts[i].startsWith("d")){
        int dValue = parts[i].substring(1).toInt();
        Serial.println(dValue);
      }
    }
  }
}

void GuessRandomVal(String a){
  int GuessedValue = a.substring(1).toInt();
  int RandomNUM = random(1,3);
  Serial.print("\n\tG: ");
  Serial.print(GuessedValue);
  Serial.print("\n\tR: ");
  Serial.print(RandomNUM);
  if(GuessedValue >= 1 && GuessedValue <= 3){
    if(GuessedValue == RandomNUM){
      Serial.println("\nCongrats, you guessed correct ");
      Serial.print(RandomNUM);
      Serial.print(" was the correct number\n");
    }else{
      Serial.println("\nunfortunately, you guessed incorrect");
      Serial.print("The correct answer was: ");
      Serial.print(RandomNUM);
    }
  }else Serial.println("\nYou need a number between 1-3\nIf you would like to try again use the command\tg[1-3]");
}

// .h num2

struct ResetValues{
  String Command;
  int ValueInput;
} RV;

void GuessRandomVal2(String a){
  int randomPickupVal = random(1,3);
  int randomDropVal = random(1,3);
  int gpValue = 0;  // guessed pickup value 
  int gdValue = 0;  // guessed drop value
  String gPart[2];

  if(a.startsWith("g")){
    int gSplit = splitString(a, ' ', gPart);
    for(int i = 0; i < gSplit; i++){
      if(gPart[i].startsWith("gp")){
        gpValue = gPart[i].substring(2).toInt();
        Serial.print("pickup value: "); Serial.println(gpValue);
      }
      if(gPart[i].startsWith("gd")){
        gdValue = gPart[i].substring(2).toInt();
        Serial.print("drop value: "); Serial.println(gdValue);
      }
    } 
  }

  if(gpValue >= 1 && gpValue <= 3 && gdValue >= 1 && gdValue <=3){
    bool bothChoicesCorrect = gpValue == randomPickupVal && gdValue == randomDropVal;
    bool oneIsCorrect = gpValue == randomPickupVal || gdValue == randomDropVal;
    bool bothChoicesWrong = gpValue != randomPickupVal && gdValue != randomDropVal;

    if(bothChoicesCorrect)
      Serial.println("\nCongrats, you guessed both correct pickup value and drop value!");
        
    if(oneIsCorrect){
      Serial.print("You guessed one correct! ");
      Serial.println(gpValue == randomPickupVal ? "pickup value was correct!" : "pickup value was wrong :(");
      Serial.println(gdValue == randomDropVal ? "drop value was correct!" : "drop value was wrong :(");
    }

    if(bothChoicesWrong)
      Serial.println("Too bad both choices are wrong!");
    }
}







