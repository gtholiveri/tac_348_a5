#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "ButtonActor.h"
#include "IntervalActor.h"
#include "LEDBlinker.h"
#include "Particle.h"
#include "RGBLED.h"
#include "Timer.h"

class TimerManager {
   public:
    int redLEDPin;
    int blueLEDPin;
    int redButtonPin;
    int blueButtonPin;

    bool* redTimerState;
    bool* blueTimerState;

    Timer redTimer;
    Timer blueTimer;

    ButtonActor redButtonActor;
    ButtonActor blueButtonActor;

    LEDBlinker timerStatusBlinker;

    IntervalActor publisher;

    RGBLED rgbled;

    TimerManager(int redLEDPin, int greenLEDPin, int blueLEDPin, int redButtonPin, int blueButtonPin, uint32_t statusBlinkOnDur, uint32_t statusBlinkOffDur);
    void endFlashSequence(int pin);
    void act();
};

#endif
