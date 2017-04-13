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
  boardA.SPIPortConnect(&SPI);      // Connect to board via SPI

  // Home system
  dSPINHome(ustepMode);
  delay(500);

  
  // Configure for run
  dSPINConfig(ustepMode); // Run config for run
  boardA.setMaxSpeed(speed_act); // Set max speed to default

  Serial.println("Init complete");

}

void loop() {
  //Measure current desired speed and endpoint positions

  speed_raw = analogRead(2);
  toppos_raw = analogRead(1);
  botpos_raw = analogRead(3);

  toppos = map(toppos_raw,0,1024,5000,20000)*(ustepMode/128);
  botpos = map(botpos_raw,0,1024,5000,20000)*(ustepMode/128);
  
  if (abs(speed_raw - speed_raw_prev) > 5) {
    // Difference between previous and current speed setting is sufficient that we know we have signal
    speed_raw_prev = speed_raw;
    speed_act = map(speed_raw,0,1024,20,450); // 1024 is max speed. 500 is max achievable at full range with large stepper
    boardA.setMaxSpeed(speed_act);

    delay(1);
    Serial.print("Top Pos: ");
    Serial.print(toppos);
    Serial.print(" | Speed: ");
    Serial.print(speed_act);
    Serial.print(" | Bottom Pos: ");
    Serial.println(botpos);     
  }

  
  if (speed_act >= 75) {
    boardA.move(FWD,toppos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();
    boardA.move(REV,toppos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();
    boardA.move(REV,botpos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();
    boardA.move(FWD,botpos);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();  
  }
}
