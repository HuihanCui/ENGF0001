#define SLAVE_ADDR 8
#include <Wire.h>
#include <string.h>

const int motorPin = 9; 
const int echoPin =A0;
float rps;
int rpm;
float time1;
float time2;
int user = 80;
double range = 1350;
char* endPointer;

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);

  Wire.begin(SLAVE_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void requestEvent() {
  char sendRPM[4];
  dtostrf(rpm, 4, 0, sendRPM);
  Serial.println(sendRPM);
  Wire.write(sendRPM);

}

void receiveEvent(int howMany)
{
  char temp = "";
  while(Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    temp += c;         // print the character
  }
  double temprange = strtod(temp, &endPointer);

  if (temprange !=  NULL) {
    range = temprange;
  }
}


void loop()
{
  time1 = pulseIn(echoPin, LOW);
  time2 = pulseIn(echoPin, HIGH);
  rps = 1000000/(2*(time1+time2));
  rpm = rps*60;

  int input = analogRead(echoPin);
  Serial.print("\nRPM: ");
  Serial.print(rpm);

  if (rpm > 1350){
    user--;
  }
  if (rpm < 650) {
    user++;
  }
  analogWrite(motorPin,user);
}