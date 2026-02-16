class RGBLED {
   public:
    int RED_PIN;
    int BLUE_PIN;
    int GREEN_PIN;

    RGBLED(int redPin, int bluePin, int greenPin)
        : RED_PIN(redPin), BLUE_PIN(bluePin), GREEN_PIN(greenPin) {}

    void smoothColorFlash() {
        
    }
};