#include "Particle.h"

#include "ButtonActor.h"
#include "LEDBlinker.h"
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

  // also general note about the verbose pointer dereferencing:
  // I did this on purpose even though I know there's a shorthand (->) just
  // so I learn exactly what's actually happening (find the actual value at
  // this pointer then do stuff with the object there)

  // the "new" keyword allocates the actual bool value on the stack and then
  // returns us the *pointer* to it, which is exactly what we want here
  TimerManager(int redLEDPin, int greenLEDPin, int blueLEDPin, int redButtonPin, int blueButtonPin, uint32_t statusBlinkOnDur, uint32_t statusBlinkOffDur) :
        blueLEDPin(blueLEDPin),
        redLEDPin(redLEDPin),
        redButtonPin(redButtonPin),
        blueButtonPin(blueButtonPin),
        redTimerState(new bool(false)),
        blueTimerState(new bool(false)),
        redTimer(7000, redTimerState),
        blueTimer(11000, blueTimerState),
        redButtonActor(false, redButtonPin, [this]() {
            if ((*this).redTimerState) {
                (*this).redTimer.stop();
                (*this).endFlashSequence((*this).redLEDPin);
            } else {
                (*this).redTimer.start();
            }
        }),
        blueButtonActor(false, blueButtonPin, [this]() {
            if ((*this).blueTimerState) {
                (*this).redTimer.stop();
                (*this).endFlashSequence((*this).blueLEDPin);
            } else {
                (*this).redTimer.start();
            }
        }),
        timerStatusBlinker(blueLEDPin, redLEDPin, redTimerState, blueTimerState, statusBlinkOnDur, statusBlinkOffDur),
        publisher(20000, 0, [this]() {
            Particle.publish("Red Timer Runs", (*this).redTimer.numRuns);
            Particle.publish("Blue Timer Runs", (*this).blueTimer.numRuns);
        }),
        rgbled(redLEDPin, greenLEDPin, blueLEDPin, COMMON_CATHODE) {}

  void endFlashSequence(int pin) {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(blueLEDPin, LOW);  // just to be safe from edge cases

    // color
    digitalWrite(pin, HIGH);
    delay(100);

    // random (pretty color wheel)
    digitalWrite(pin, LOW);
    rgbled.writeColorWheel(3);  // this does the delaying for us in this case

    // color
    digitalWrite(pin, HIGH);
    delay(100);

    // random
    digitalWrite(pin, LOW);
    rgbled.writeColorWheel(3);

    // color
    digitalWrite(pin, HIGH);
    delay(100);

    digitalWrite(pin, LOW);
  }

  void act() {
    redButtonActor.act();
    blueButtonActor.act();
    redTimer.act();
    blueTimer.act();
    timerStatusBlinker.act();
  }
};