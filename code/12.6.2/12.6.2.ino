int sens = 512;
long last = 0;
int period = 200;
int stat = LOW;
int stat2 = LOW;
int input;
int counter = 0;
int time1 = 0;
int time2 = 0;
int rpm2;
int user = 50;

volatile int pwm_value = 0;
volatile int prev_time = 0;
 
void setup() {
  // when pin D2 goes high, call the rising function
  
  Serial.begin(115200);
  pinMode(A0,INPUT);
  attachInterrupt(0, rising, RISING);
  analogWrite(9,user);
}

void loop(){
  attachInterrupt(0, rising, RISING);
} 
 
void rising() {
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(0, rising, RISING);
  pwm_value = micros()-prev_time;
  Serial.print(pwm_value);
}



