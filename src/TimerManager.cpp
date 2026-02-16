#include "TimerManager.h"

#include "ButtonActor.h"
#include "LEDBlinker.h"
#include "Particle.h"
#include "RGBLED.h"
#include "Timer.h"

// also general note about the verbose pointer dereferencing:
// I did this on purpose even though I know there's a shorthand (->) just
// so I learn exactly what's actually happening (find the actual value at
// this pointer then do stuff with the object there)

// the "new" keyword allocates the actual bool value on the stack and then
// returns us the *pointer* to it, which is exactly what we want here
TimerManager::TimerManager(int redLEDPin, int greenLEDPin, int blueLEDPin, int redButtonPin, int blueButtonPin, uint32_t statusBlinkOnDur, uint32_t statusBlinkOffDur)
    : blueLEDPin(blueLEDPin),
      redLEDPin(redLEDPin),
      redButtonPin(redButtonPin),
      blueButtonPin(blueButtonPin),
      redTimerState(new bool(false)),
      blueTimerState(new bool(false)),
      redTimer(7000, redTimerState, [this]() {
        (*this).endFlashSequence((*this).redLEDPin);
        // derefence this, call the flash sequence on (dereference this, get the led pin)
      }),
      blueTimer(11000, blueTimerState, [this]() {
        (*this).endFlashSequence((*this).blueLEDPin);
      }),
      redButtonActor(false, redButtonPin,
                     [this]() {
                       if (*(*this).redTimerState) {
                         // this is a pointer so we dereference it first inside parentheses
                         // redTimerState is also a pointer so we need to dereference that too
                         // otherwise we are checking if it's not null rather than
                         // whether the bool is true / false
                         (*this).redTimer.stop();
                       } else {
                         (*this).redTimer.start();
                       }
                     }),
      blueButtonActor(false, blueButtonPin,
                      [this]() {
                        if (*(*this).blueTimerState) {
                          (*this).blueTimer.stop();
                        } else {
                          (*this).blueTimer.start();
                        }
                      }),
      timerStatusBlinker(blueLEDPin, redLEDPin, redTimerState, blueTimerState, statusBlinkOnDur, statusBlinkOffDur),
      publisher(20000, 0,
                [this]() {
                  Particle.publish("Red Timer Runs", (*this).redTimer.numRuns);
                  Particle.publish("Blue Timer Runs", (*this).blueTimer.numRuns);
                }),
      rgbled(redLEDPin, greenLEDPin, blueLEDPin, COMMON_CATHODE) {}

void TimerManager::endFlashSequence(int pin) {
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

void TimerManager::act() {
  redButtonActor.act();
  blueButtonActor.act();
  redTimer.act();
  blueTimer.act();
  timerStatusBlinker.act();
  publisher.act();
}