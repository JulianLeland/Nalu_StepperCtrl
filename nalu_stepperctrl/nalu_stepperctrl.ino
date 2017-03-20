#include <SparkFunAutoDriver.h>
#include <SPI.h>

AutoDriver boardA(0, 10, 6); // Syntax: position, CS pin, reset pin, busy pin

int speed_raw = 256; // Initialize at 50% speed
int speed_raw_prev = 256; //Initialize at 50% speed
int speed_act = 150;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.println("Beginning init");
  // Start by setting up the pins and the SPI peripheral.
  //  The library doesn't do this for you! 
  pinMode(6, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  
  digitalWrite(10, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(6, HIGH);
  delay(1000);
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  boardA.SPIPortConnect(&SPI);      // Before doing anything else, we need to
  dSPINConfig(); 

  boardA.setMaxSpeed(speed_act);
  boardA.setFullSpeed(speed_act);

  Serial.println("Init complete");

}

void loop() {
  //Measure current desired speed and endpoint positions

  speed_raw = analogRead(A0);
  if (abs(speed_raw - speed_raw_prev) > 5) {
    //Difference between previous and current speed setting is sufficient that we know we have signal
    speed_raw_prev = speed_raw;
    speed_act = map(speed_raw,64,1024,50,1030); //Appears that 1024 is max achievable speed for 
    boardA.setMaxSpeed(speed_act);
    Serial.println(speed_act);
  }
  
  if (speed_act >= 50) {
    boardA.move(FWD,5000);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();
    boardA.move(REV,5000);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();
    boardA.move(REV,5000);
    while (boardA.busyCheck()) {
      delay(1);
    }
    //boardA.softStop();
    boardA.move(FWD,5000);
    while (boardA.busyCheck()) {
      delay(1);
    }
    boardA.softStop();  
  }
}
