#include <Wire.h>

int input;
long last = 0;
int stat = LOW;
int stat2;
int sens = 128;
int slots = 2;
int counter = 0;
int milisecs = 500;
double rpm;
int motorControl = 9;

void setup() {
  Serial.begin(9600);
  input = ((analogRead(A0)+1)/4)-1;
  delay(10);
  pinMode(motorControl, OUTPUT);  
  analogWrite(9,255);
} 

//input 0-1023
//output 0-255 3v
void loop() {
  input = ((analogRead(A0)+1)/4)-1;
  //Serial.print("\nA0:");
  if (input<sens){
    stat = LOW;
  }
  else{
    stat = HIGH;
  }
  if (stat2!=stat){
    counter++;
    stat2 = stat;
  }
  if (millis()-last>=milisecs){
    double rpm = ((double)counter/slots)/2 * 60000 / milisecs;
    Serial.print("\nRPM:");
    Serial.print(rpm);
    counter = 0;
    last = millis();
  }
  
  delay(10);
  analogWrite(motorControl,255);


  //if (rpm<600){
    //digitalWrite(motorControl, 255);
  //}
  //if (rpm>1400){
    //digitalWrite(motorControl, 100);
  //}
  
}


//if (input < sens){
    //stat = LOW;
  //}
  //else{
    //stat = HIGH;
  //}

  //if (stat2 != stat){
    //counter++;
    //stat2 = stat;
  //}

 // if (millis()-last >= period){
    //double rpm = ((double)counter /2 ) * 60000 / period;
    //double rpm = counter *30;
    //Serial.print("\nRPM:");
    //Serial.print(rpm);
    //counter = 0;
    //last = millis();
  //}
  //time1 = pulseIn(A0, HIGH);
  //time2 = pulseIn(A0, LOW);
  //rpm2 = 30000/(time1+time2);
  //Serial.print("\nRPM:");
  //Serial.print(rpm2);