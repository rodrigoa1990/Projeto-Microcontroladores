#include <Stepper.h>
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define STEPS 100
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;



int melody[]={NOTE_E2,NOTE_E2,NOTE_E2,NOTE_C2,NOTE_G2,NOTE_E2,NOTE_C2,NOTE_G2,NOTE_E2,NOTE_B2,NOTE_B2,NOTE_B2,NOTE_C3,NOTE_G2,NOTE_DS2,NOTE_C2,NOTE_G2,NOTE_E2};
int noteDurations[] = {2,2,2,4,4,2,4,4,2,2,2,2,4,4,2,4,4,2};

int analogPin3 = 3;
int analogPin2 = 1;
int analogPin = 0;
int Control1 = 3;
int Control2 = 5;
int Intensity = 6;
volatile int inter = 0;
int LED1 = 13;
int LED2 = 14;
Stepper stepper(STEPS, 10, 9, 11, 12);

int dir = 0;
String baixo = "Baixo                   ";
String cima = "Cima                         ";
String abrir = "Abrir                   ";
String fechar = "Fechar                       ";
String musica = "Automatico                       ";



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
  Serial.begin(9600);  
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
void Play(){ 

   for (int thisNote = 0; thisNote < 18; thisNote++) {
   int noteDuration = 1000 / noteDurations[thisNote];
   tone(8, melody[thisNote], noteDuration);
   int pauseBetweenNotes = noteDuration * 1.30;
   delay(pauseBetweenNotes);
   noTone(8);}  

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
    lcd.print(musica);   
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
