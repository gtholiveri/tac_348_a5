#include "Particle.h"
#include "TimerManager.h"

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_WARN);

// const int PIN = <pin>;
const int BUTTON_R = D2;
const int BUTTON_B = D1;
const int LED_R = A5;
const int LED_G = MOSI;
const int LED_B = MISO;


TimerManager manager(LED_R, LED_G, LED_B, BUTTON_R, BUTTON_B, 200, 800);

void setup() {
    Serial.begin(9600);
    // pinMode(pin, mode);
    pinMode(BUTTON_R, INPUT);
    pinMode(BUTTON_B, INPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
}


void loop() {
    manager.act();
}