#include <Arduino.h>
#include "macros.h"
#include "functions.h"
#include <IntervalTimer.h>

volatile int currentEncoderVal = INIT;
// Create an IntervalTimer object 
IntervalTimer myTimer;
extern volatile int frontCount;
extern volatile int midCount;
extern volatile int backCount;




void setup() {
    
    init_encoderCounter();

}

void loop() {


}

