int input;
int time1;
int time2;
int rpm2;
int stat;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(9,OUTPUT);
  analogWrite(9,150);
  //input = analogRead (A0);
}


void loop() {
  // put your main code here, to run repeatedly:


  time1 = pulseIn(A0, HIGH);
  time2 = pulseIn(A0, LOW);

  //for (int i=1; i<=150; i++){
    //analogWrite(9,150);
 // }

  rpm2 = 30000000/(time1+time2);
  Serial.print("\ntime1:");
  Serial.print(time1);
  
  Serial.print("\ntime2:");
  Serial.print(time2);

  //delay(10);

}
