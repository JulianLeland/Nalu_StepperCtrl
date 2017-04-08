void dSPINConfig(int ustepMode)
{
  // This is the configuration function for the two dSPIN parts. Read the inline
  //  comments for more info.
  
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  switch (ustepMode) {
    case 128:{
      boardA.configStepMode(STEP_FS_128);   // 0 microsteps per step  
    }
    case 64:{
      boardA.configStepMode(STEP_FS_64);   // 0 microsteps per step
    }
    case 32:{
      boardA.configStepMode(STEP_FS_32);   // 0 microsteps per step
    }
    case 16:{
      boardA.configStepMode(STEP_FS_16);   // 0 microsteps per step
    }
    case 8:{
      boardA.configStepMode(STEP_FS_8);   // 0 microsteps per step
    }
    case 4:{
      boardA.configStepMode(STEP_FS_4);   // 0 microsteps per step
    }
    case 2:{
      boardA.configStepMode(STEP_FS_2);   // 0 microsteps per step
    }
    case 1:{
      boardA.configStepMode(STEP_FS);   // 0 microsteps per step
    }
    default:{
      boardA.configStepMode(STEP_FS_128);   // 0 microsteps per step
    }
  }
  boardA.setMaxSpeed(1024);        // 1025 steps/s max
  boardA.setFullSpeed(0);       // microstep below 10000 steps/s
  
  float accel = 15000;// 20000*(ustepMode/128);
  boardA.setAcc(accel);             // accelerate at 10000 steps/s/s
  boardA.setDec(accel);
  
  
  boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_6000mA);  // OC threshold 2250 mA
//  boardA.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  boardA.setOCShutdown(OC_SD_ENABLE); // don't shutdown on OC
  boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
//  boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
//  boardA.setOscMode(INT_16MHZ); // for boardA, we want 16MHz
                                    //  external osc, 16MHz out. boardB
                                    //  will be the same in all respects
                                    //  but this, as it will generate the
                                    //  clock.
  boardA.setAccKVAL(200);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(200);
  boardA.setRunKVAL(200);
  boardA.setHoldKVAL(200);           // This controls the holding current; keep it low..
}
