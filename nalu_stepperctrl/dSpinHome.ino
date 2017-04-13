void dSPINHome(int ustepMode) 
{
  // This section is the same as dSPINConfig - just setting p
  boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  switch (ustepMode) {
    case 128:{
      boardA.configStepMode(STEP_FS_128);   // 128 microsteps per step  
    }
    case 64:{
      boardA.configStepMode(STEP_FS_64);   // 64 microsteps per step
    }
    case 32:{
      boardA.configStepMode(STEP_FS_32);   // 32 microsteps per step
    }
    case 16:{
      boardA.configStepMode(STEP_FS_16);   // 16 microsteps per step
    }
    case 8:{
      boardA.configStepMode(STEP_FS_8);   // 8 microsteps per step
    }
    case 4:{
      boardA.configStepMode(STEP_FS_4);   // 4 microsteps per step
    }
    case 2:{
      boardA.configStepMode(STEP_FS_2);   // 2 microsteps per step
    }
    case 1:{
      boardA.configStepMode(STEP_FS);   // 0 microsteps per step
    }
    default:{
      boardA.configStepMode(STEP_FS_128);   // Default: 128 microsteps per step
    }
  }
  
  boardA.setMaxSpeed(1024);        // 1025 steps/s max
  boardA.setFullSpeed(1024);       // microstep below 10000 steps/s
  
  boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  boardA.setOCThreshold(OC_2625mA);  // OC threshold 2250 mA
  boardA.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
  boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V

  // These parameters are changed for homing run
  float accel = 30000;// 20000*(ustepMode/128);
  boardA.setAcc(accel);             // accelerate at 10000 steps/s/s
  boardA.setDec(accel);
  
  boardA.setAccKVAL(100);           // We'll tinker with these later, if needed.
  boardA.setDecKVAL(100);
  boardA.setRunKVAL(50);
  boardA.setHoldKVAL(10);           // This controls the holding current; keep it low.

  // Move to home location
  boardA.setMaxSpeed(100); // Set low speed
  boardA.move(REV,50000); // Move backwards 50000 counts --> ensure we hit rear endstop
  while (boardA.busyCheck()) {
      delay(1);
    }
  boardA.softStop();
  boardA.move(FWD,25000); // Move forwards to home position
  while (boardA.busyCheck()) {
      delay(1);
    }
  boardA.softStop();
  
}

