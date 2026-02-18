#include "LEDBlinker.h"

#include <map>

#include "IntervalActor.h"

uint32_t lastFiringTime = 0;


LEDBlinker::LEDBlinker(int blueLEDPin, int redLEDPin, bool* redTimerState, bool* blueTimerState, uint32_t onDuration, uint32_t offDuration)
    : firstOnActor(onDuration + offDuration, 0, [blueLEDPin, redLEDPin, redTimerState, blueTimerState]() {
        if (*redTimerState && !*blueTimerState) {
            digitalWrite(redLEDPin, HIGH);
        } else if (*blueTimerState && !*redTimerState) {
            digitalWrite(blueLEDPin, HIGH);
        } else if (*blueTimerState && *redTimerState) {
            // arbitrary choice: red will go first in the cardinal order
            digitalWrite(redLEDPin, HIGH);
        } else {
            // do nothing, no timers are on
        }
        /*
        This debug code was critical (ported from dedicated testing project because
        the debugging this whole thing was brutal)
        uint32_t currTime = millis();
        double currTimeS = currTime / 1000.0;
        double deltaS = (currTime - lastFiringTime) / 1000.0;
        Serial.print("FIRST ON FIRED AT T =  ");
        Serial.print(currTimeS);
        Serial.print(", ");
        Serial.print(deltaS);
        Serial.println(" s after prev");
        lastFiringTime = currTime;
        */


    }),
    secondOnActor(onDuration + offDuration, onDuration / 2, [blueLEDPin, redLEDPin, redTimerState, blueTimerState]() {
        if (*redTimerState && !*blueTimerState) {
            // the red LED should usually already be on in this case, but
            // there are certain cases where the timer might have been started
            // right after the check so we'll write high here even though
            // technically redundant
            digitalWrite(redLEDPin, HIGH);
        } else if (*blueTimerState && !*redTimerState) {
            // same reasoning as previous branch, we'll write high again even if
            // redundant for edge cases
            digitalWrite(blueLEDPin, HIGH);
        } else if (*blueTimerState && *redTimerState) {
            // we want to be splitting the on duration, so in this case
            // we toggle off the red LED (which occupied the first half)
            // and toggle on the blue LED (which will now occupy the second)
            digitalWrite(redLEDPin, LOW);
            digitalWrite(blueLEDPin, HIGH);
        } else {
            // do nothing, no timers are on
        }
        /*
        uint32_t currTime = millis();
        double currTimeS = currTime / 1000.0;
        double deltaS = (currTime - lastFiringTime) / 1000.0;
        Serial.print("SECOND ON FIRED AT T = ");
        Serial.print(currTimeS);
        Serial.print(", ");
        Serial.print(deltaS);
        Serial.println(" s after prev");
        lastFiringTime = currTime;
        */
    }),
    offActor(onDuration + offDuration, onDuration, [blueLEDPin, redLEDPin, redTimerState, blueTimerState]() {
        if (*redTimerState) {
            digitalWrite(redLEDPin, LOW);
        }
        if (*blueTimerState) {
            digitalWrite(blueLEDPin, LOW);
        }
        /*
        uint32_t currTime = millis();
        double currTimeS = currTime / 1000.0;
        double deltaS = (currTime - lastFiringTime) / 1000.0;
        Serial.print("OFF FIRED AT T =       ");
        Serial.print(currTimeS);
        Serial.print(", ");
        Serial.print(deltaS);
        Serial.println(" s after prev");
        lastFiringTime = currTime;
        */
    }) {}

void LEDBlinker::act() {
  firstOnActor.act();
  secondOnActor.act();
  offActor.act();
}