#include <Arduino.h>
#include "Timer.h"
#define GPIOPin 4

Timer T;


// Called Automatically by an expired timer
void HandleTimer(TimerInstance *T)
{
    Serial.printf("HandlerTimer is called with %s\n",T->TimerName);
    digitalWrite(GPIOPin, 1-digitalRead(GPIOPin));  // Toggle LED
}    

void setup() {
  Serial.begin(115200);

           // TimerName,      mS, Recurring,  Callback Function
  T.AddTimer("OneSecond",  1000, true,       HandleTimer);      // After 1 second, calls HandleTimer. Retriggers
  T.AddTimer("ThreeSecond",  3000, true,       HandleTimer);      // After 3 seconds, calls HandleTimer. Retriggers
  T.AddTimer("FiveSecond",  5000, false,      HandleTimer);     // After 3 seconds, calls HandleTimer. Does not retrigger
}

void loop()
{
  T.loop();    
}