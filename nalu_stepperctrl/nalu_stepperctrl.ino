#include <SparkFunAutoDriver.h>
#include <SPI.h>

AutoDriver boardA(0, 10, 6); // Syntax: position, CS pin, reset pin, busy pin


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

  Serial.println("Init complete");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Beginning loop");
  boardA.move(FWD,10000);
  delay(5000);
//  while (boardA.busyCheck())
//  boardA.softStop();
  boardA.move(REV,10000);
  delay(5000);
//  while (boardA.busyCheck())
//  boardA.softStop();
  Serial.println("Loop iteration complete");

}
