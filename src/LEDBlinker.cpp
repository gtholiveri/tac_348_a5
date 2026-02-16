#include <map>
#include "IntervalActor.h"

class LEDBlinker {
   public:
    int blueLEDPin;
    int redLEDPin;

    IntervalActor firstOnActor;
    IntervalActor secondOnActor;
    IntervalActor offActor;

    // these come from the central orchestrator class
    // they *must* be pointers so that the values always update across
    bool* redTimerState;
    bool* blueTimerState;

    LEDBlinker(int blueLEDPin, int redLEDPin, bool* redTimerState, bool* blueTimerState, uint32_t onDuration, uint32_t offDuration) :
        firstOnActor(onDuration + offDuration, 0, [blueLEDPin, redLEDPin, redTimerState, blueTimerState]() {
            if (redTimerState && !blueTimerState) {
                digitalWrite(redLEDPin, HIGH);
            } else if (*blueTimerState && !*redTimerState) {
                digitalWrite(blueLEDPin, HIGH);
            } else if (*blueTimerState && *redTimerState) {
                // arbitrary choice: red will go first in the cardinal order
                digitalWrite(redLEDPin, HIGH);
            } else {
                // do nothing, no timers are on
            }
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
        }),
        offActor(onDuration + offDuration, onDuration, [blueLEDPin, redLEDPin, redTimerState, blueTimerState]() {
            if (redTimerState) {
                digitalWrite(redLEDPin, LOW);
            }
            if (blueTimerState) {
                digitalWrite(blueLEDPin, LOW);
            }
        }) {}

    void act() {
        firstOnActor.act();
        secondOnActor.act();
        offActor.act();
    }
};