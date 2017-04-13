#include <SparkFunAutoDriver.h>
#include <SPI.h>

AutoDriver boardA(0, 10, 9); // Syntax: position, CS pin, reset pin, busy pin

int ustepMode = 128; // Number of microsteps to use

int speed_raw = 256; // Initialize at 50% speed
int speed_raw_prev = 256; //Initialize at 50% speed
int speed_act = 150;

int toppos_raw = 0;
int botpos_raw = 0;
int toppos = 5000*(ustepMode/128);
int botpos = 5000*(ustepMode/128);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.println("Beginning init");
  // Start by setting up the pins and the SPI peripheral.
  //  The library doesn't do this for you! 
  pinMode(9, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(9, HIGH);
  delay(1000);
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  boardA.SPIPortConnect(&SPI);      // Before doing anything else, we need to
  dSPINConfig(ustepMode); 

  boardA.setMaxSpeed(speed_act);
  boardA.setFullSpeed(speed_act);

  Serial.println("Init complete");

}

void loop() {
  //Measure current desired speed and endpoint positions

  speed_raw = analogRead(A1);
  toppos_raw = analogRead(A2);
  botpos_raw = analogRead(A0);

  toppos = map(toppos_raw,64,1024,5000,20000)*(ustepMode/128);
  botpos = map(botpos_raw,64,1024,5000,20000)*(ustepMode/128);  
  
  if (abs(speed_raw - speed_raw_prev) > 5) {
    // Difference between previous and current speed setting is sufficient that we know we have signal
    speed_raw_prev = speed_raw;
    speed_act = map(speed_raw,0,1024,10,475); // 1024 is max speed. 500 is max achievable at full range with large stepper
    boardA.setMaxSpeed(speed_act);
    Serial.println(speed_act);
  }
  
  if (speed_act >= 50) {
    boardA.move(FWD,toppos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.hardStop();
    boardA.move(REV,toppos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.hardStop();
    boardA.move(REV,botpos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.hardStop();
    boardA.move(FWD,botpos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.hardStop();  
  }
}
