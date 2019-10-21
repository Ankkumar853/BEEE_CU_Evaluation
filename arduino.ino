#define waterInlet 5
#define drainValve 4
#define forMotor 3
#define revMotor 2
#define goButton A1
#define wlSensor 7
#define goLight 0
#define stopLight 1
#define stopButton A3
#define doorSensor A0
 
void setup () {
 
  pinMode(waterInlet, OUTPUT);
  pinMode(drainValve, OUTPUT);
  pinMode(forMotor, OUTPUT);
  pinMode(revMotor, OUTPUT);
  pinMode(goButton, INPUT);
  pinMode(stopButton, INPUT);
  digitalWrite(stopButton, HIGH);
  pinMode(wlSensor, INPUT_PULLUP);
  pinMode(doorSensor, INPUT);
  digitalWrite(doorSensor, HIGH);
  pinMode(goLight, OUTPUT);
  pinMode(stopLight, OUTPUT);
}
 
void fillItUp() {
  if (digitalRead(wlSensor) == LOW)
     {
     digitalWrite(waterInlet, HIGH);
     delay (1000);
     }
     else {
       digitalWrite(waterInlet, LOW);
       delay(1000);
     }
}
 
void drainItOut() {
  unsigned long drainTime = millis();
  digitalWrite(drainValve, HIGH);
  delay(500);
  while ((millis() - drainTime) < 100000) {  // Assuming that the water drains within 100 seconds.
    delay(100);
  }
  digitalWrite(drainValve, LOW);
  delay(100);
}

void washPhase() {
  for (int i=0; i < 20; i++){
  digitalWrite(forMotor, HIGH);
  delay(5000);
  digitalWrite(forMotor, LOW);
  delay(1000);
  digitalWrite(revMotor, HIGH);
  delay(5000);
  digitalWrite(revMotor, LOW);
  delay(1000);
  }
}
 
void ppreDry() {
  digitalWrite(drainValve, HIGH);
  delay(1000);
  digitalWrite(forMotor, HIGH);
  delay(5000);
  digitalWrite(forMotor, LOW);
  delay(2000);
  digitalWrite(forMotor, HIGH);
  delay(7000);
  digitalWrite(forMotor, LOW);
  delay(2000);
  digitalWrite(forMotor, HIGH);
  delay(10000);
  digitalWrite(forMotor, LOW);
  delay(2000);
}

void preDry() {
  unsigned long dryTime = millis();
  digitalWrite(forMotor, HIGH);
  delay(500);
  while ((millis() - dryTime) < 120000) { // pre dry for 120 seconds
    delay(500);
  }
  digitalWrite(forMotor, LOW);
  digitalWrite(drainValve, LOW);
  delay(500);
}
 
void finalDry() {
  unsigned long fdryTime = millis();
  digitalWrite(forMotor, HIGH);
  delay(500);
  while ((millis() - fdryTime) < 300000) { // final dry for 300 seconds
    delay(500);
  }
  digitalWrite(forMotor, LOW);
  digitalWrite(drainValve, LOW);
  delay(500);
}

void loop() {

  // Go button was pressed, run through the cycles
  digitalWrite(goLight, HIGH);
  digitalWrite(stopLight, HIGH);
  // Washing
  fillItUp();
  delay(1000);
  washPhase();
  delay(1000);
  drainItOut();
  delay(1000);
  ppreDry();
  delay(1000);
  preDry();
  delay(1000);
  // Rinsing 1
  fillItUp();
  delay(1000);
  washPhase();
  delay(1000);
  drainItOut();
  delay(1000);
  ppreDry();
  delay(1000);
  preDry();
  delay(1000);
  // Rinsing 2
  fillItUp();
  delay(1000);
  washPhase();
  delay(1000);
  drainItOut();
  delay(1000);
  //Spin dry
  ppreDry();
  delay(1000);
  preDry();
  delay(1000);
  finalDry();
  digitalWrite(goLight, LOW);
  digitalWrite(stopLight, HIGH);
}
