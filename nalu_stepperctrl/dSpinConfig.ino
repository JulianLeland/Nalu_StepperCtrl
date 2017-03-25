void dSPINConfig(void)
{
  // This is the configuration function for the two dSPIN parts. Read the inline
  //  comments for more info.
  
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
//  boardA.configStepMode(STEP_FS);   // 0 microsteps per step
  boardA.setMaxSpeed(1025);        // 1025 steps/s max
  boardA.setFullSpeed(512);       // microstep below 10000 steps/s
  
  float accel = 20000;
  boardA.setAcc(accel);             // accelerate at 10000 steps/s/s
  boardA.setDec(accel);
  
  
  boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_2250mA);  // OC threshold 750mA
//  boardA.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardA.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
  boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
//  boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
//  boardA.setOscMode(INT_16MHZ); // for boardA, we want 16MHz
                                    //  external osc, 16MHz out. boardB
                                    //  will be the same in all respects
                                    //  but this, as it will generate the
                                    //  clock.
  boardA.setAccKVAL(250);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(250);
  boardA.setRunKVAL(250);
  boardA.setHoldKVAL(64);           // This controls the holding current; keep it low..
}
