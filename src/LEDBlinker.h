#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include "IntervalActor.h"

class LEDBlinker {
   public:
    int blueLEDPin;
    int redLEDPin;

    IntervalActor firstOnActor;
    IntervalActor secondOnActor;
    IntervalActor offActor;

    bool* redTimerState;
    bool* blueTimerState;

    LEDBlinker(int blueLEDPin, int redLEDPin, bool* redTimerState, bool* blueTimerState, uint32_t onDuration, uint32_t offDuration);
    void act();
};

#endif
