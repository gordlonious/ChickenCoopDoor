#ifndef chickencoopdoor_data_h
  #define chickencoopdoor_data_h
  #include "chickencoopdoor_data.h"
#endif

bool DoorIsOpen = false; // assume door is shut to start with (night)

void setup() {
  pinMode(StepperPin1, OUTPUT); // each output pin can provide ~40mA of current to external hardware
  pinMode(StepperPin2, OUTPUT);
}

void loop() 
{
  LightData ld = CheckForConsistentLightReading(3);
  if(ld.isConsistent) 
  {
    // change state of door if it has changed
    if(ld.lightLevel == 3 && !DoorIsOpen || ld.lightLevel == 1 && DoorIsOpen)
    {
      digitalWrite(StepperPin1, HIGH);
      digitalWrite(StepperPin2, HIGH);

      delay(3000); // how long does it take to change the door state? 
      // TODO: Change voltage levels in a particular way to signal/differentiate between 'open' and 'close' motor operations (use motor control pins)

      digitalWrite(StepperPin1, LOW);
      digitalWrite(StepperPin2, LOW);
    }
  }
}

// param 1: duration (in seconds) that the light level is consistently 'light' or 'dark' before returning
// returns: true if light level is consistently 'light' or 'dark' for the specified duration
// TODO: decrease amount of reads (include delay, effects duraction math)
LightData CheckForConsistentLightReading(int dur) {
  int nor = 1000000 * dur / 100;
  LightData ld;
  int initialRead = readLight();
  for(int i = 0; i < nor; i++) {
    int d = readLight();
    if(d != initialRead) {
      ld.isConsistent = false;
      return ld;
    }
    if(i+1 == nor) {
      ld.lightLevel = d;
      ld.isConsistent = true;
      return ld;
    }
  }
  ld.isConsistent = false;
  return ld;
}

// returns 1 if analog read from light pin was in night range
// returns 2 if read was in nuetral range
// returns 3 if read was in day range
int readLight() {
  int d = analogRead(DaylightPin); // 1 read takes ~100 microseconds
  if(d >= NightMin && d <= NightMax) {
    return 1;
  } else if(d > NightMax && d < DayMin) {
    return 2;
  } else if(d >= DayMin && d <= DayMax) {
    return 3;
  } else { return 0; }
}
