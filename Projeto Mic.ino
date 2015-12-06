#include <Stepper.h>
#define STEPS 100
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;




int analogPin3 = 3;
int analogPin2 = 1;
int analogPin = 0;
int Control1 = 3;
int Control2 = 5;
int Intensity = 6;
volatile int inter = 0;
Stepper stepper(STEPS, 10, 9, 11, 12);
 
int dir = 0;
String baixo = "Baixo                   ";
String cima = "Cima                         ";
String abrir = "Abrir                   ";
String fechar = "Fechar                       ";
String automa = "Automatico                       ";



int val4 = 0;
int val =0;
int val2 = 0;
int val3 = 0;
int previous = 0;

void setup() {
  // initialize the digital pin as an output.
  pinMode(Control1, OUTPUT);
  pinMode(Control2, OUTPUT);
  pinMode(Intensity, OUTPUT);
  stepper.setSpeed(90);
  attachInterrupt(0,Interromper,FALLING);
  lcd.begin(16, 2);
}

void Interromper(){

  if(inter == 0){
    inter =1;}
    else{
      if(inter == 1){
      inter = 2;
      }
       else{
    if(inter == 2){inter = 0;}
       }
           }
 
  }

void loop() {
  while(inter == 0){
  val = analogRead(analogPin);

 
  if(val < 611){
   val2= map(val, 0,611,255,0);
   	digitalWrite(Control2, HIGH);
  	digitalWrite(Control1, LOW);
        analogWrite(Intensity,val2);
        lcd.clear();
        lcd.setRGB(0, 100, 0);
        lcd.print(cima);

  }
  else{
   val2= map(val,611,1023,0,255);
   digitalWrite(Control2, LOW);
  digitalWrite(Control1, HIGH);
  analogWrite(Intensity,val2);
  lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(baixo);  
  }
  }
  while(inter == 2){
      lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(automa);   
   val4 = analogRead(analogPin3);
   val3 = map(val4, 0 ,781, 0, 500);
   stepper.step(val3- previous);
   Serial.println(val3);
   previous = val3;

   
   

  delay(1000);
  }
  while(inter == 1){
       digitalWrite(Control2, LOW);
  digitalWrite(Control1, LOW);
    
    val3 = analogRead(analogPin2); 
    val4 = map(val3,0,1023,0,500);
    stepper.step(val4- previous);
    val2 = val4- previous;
    previous = val4;
    
     if(val2 >= 0){
        lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(abrir);        
      }
      else{
      lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(fechar);  
      }   
  }
  
}
