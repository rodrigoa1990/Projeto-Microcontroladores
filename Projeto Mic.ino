#include <Stepper.h>
#define STEPS 100
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;




int analogPin3 = 3; //Sensor de LUZ
int analogPin2 = 1; // Potenciometro1  
int analogPin = 0;//Potenciometro 2

int Control1 = 3;// HBridge 1
int Control2 = 5;//HBridge 2
int Intensity = 6;//PWM HBridge

volatile int inter = 0;//variavel de interrupcao

Stepper stepper(STEPS, 10, 9, 11, 12);//Stepper
 
String baixo = "Baixo                   ";
String cima = "Cima                         ";
String abrir = "Abrir                   ";
String fechar = "Fechar                       ";
String automa = "Automatico                       ";


//Variaveis Usadas
int val4 = 0;
int val =0;
int val2 = 0;
int val3 = 0;
int previous = 0;

void setup() {
  pinMode(Control1, OUTPUT);
  pinMode(Control2, OUTPUT);
  pinMode(Intensity, OUTPUT);
  stepper.setSpeed(90);
  attachInterrupt(0,Interromper,FALLING);
  lcd.begin(16, 2);
}

void Interromper(){ // Interrupcao de 1,2,3

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
        delay(100);


  }
  else{
   val2= map(val,611,1023,0,255);
   digitalWrite(Control2, LOW);
  digitalWrite(Control1, HIGH);
  analogWrite(Intensity,val2);
  lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(baixo);  
    delay(100);
  }
  }
  while(inter == 2){
           digitalWrite(Control2, LOW);
  digitalWrite(Control1, LOW);
      lcd.clear();
      lcd.setRGB(100, 100, 100);
    lcd.print(automa);   
   val4 = analogRead(analogPin3);
   val3 = map(val4, 0 ,781, 0, 200);
   stepper.step(val3- previous);
   previous = val3;

   
   

  delay(1000);
  }
  while(inter == 1){
       digitalWrite(Control2, LOW);
  digitalWrite(Control1, LOW);
    
    val3 = analogRead(analogPin2); 
    val4 = map(val3,0,1023,0,200);
    val2 = val4- previous;
     if(val2 >= 0){
        lcd.clear();
      lcd.setRGB(100, 0, 0);
    lcd.print(abrir);        
      }
      else{
      lcd.clear();
      lcd.setRGB(0, 0, 100);
    lcd.print(fechar);  
      } 
      delay(10);
    
    stepper.step(val4- previous);
    
    previous = val4;
    
      
  }
  
