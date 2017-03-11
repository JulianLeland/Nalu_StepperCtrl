#include <SparkFunAutoDriver.h>
#include <SPI.h>

AutoDriver boardA(0, 10, 6);


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
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  dSPINConfig(); 

  Serial.println("Init complete");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Beginning loop");
  boardA.run(FWD,3000);
  delay(1000);
  boardA.softStop();
  boardA.run(REV,3000);
  delay(1000);
  boardA.softStop();
  Serial.println("Loop iteration complete");

}

// This is the configuration function for the two dSPIN parts. Read the inline
//  comments for more info.
void dSPINConfig(void)
{
  boardA.SPIPortConnect(&SPI);      // Before doing anything else, we need to
  
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  boardA.configStepMode(STEP_FS);   // 0 microsteps per step
  boardA.setMaxSpeed(100000);        // 10000 steps/s max
  boardA.setFullSpeed(100000);       // microstep below 10000 steps/s
  boardA.setAcc(0xFFF);             // accelerate at 10000 steps/s/s
  boardA.setDec(0xFFF);
  boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_750mA);  // OC threshold 750mA
  boardA.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardA.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
  boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
  boardA.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                    //  external osc, 16MHz out. boardB
                                    //  will be the same in all respects
                                    //  but this, as it will generate the
                                    //  clock.
  boardA.setAccKVAL(255);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(255);
  boardA.setRunKVAL(255);
  boardA.setHoldKVAL(32);           // This controls the holding current; keep it low..
}
