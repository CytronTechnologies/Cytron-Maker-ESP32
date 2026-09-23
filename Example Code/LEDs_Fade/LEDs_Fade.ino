/*
  DESCRIPTION:
  Smooth LED fading effect for all onboard LEDs.

  All onboard LEDs gradually increase in brightness from off to full
  brightness, then gradually decrease back to off. The fade cycle
  repeats continuously with a short pause between each cycle.

  AUTHOR:
  Cytron Technologies Sdn Bhd

  WEBSITE:
  https://www.cytron.io

  EMAIL:
  support@cytron.io
*/

// LED pins
const int ledPins[] = {
  2, 12, 13, 16, 17, 18, 19,
  21, 22, 23, 25, 27, 32, 33
};

const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// LED fading settings
const int fadeStepDelay = 5;
const int pauseDuration = 500;

const int maximumBrightness = 255;


// Set the brightness of all LEDs.
void setLedBrightness(int brightness)
{
  for (int i = 0; i < ledCount; i++) {
    ledcWrite(ledPins[i], brightness);
  }
}


void setup()
{
  // Attach PWM to all LED pins.
  for (int i = 0; i < ledCount; i++) {
    ledcAttach(ledPins[i], 5000, 8);
  }
}


void loop()
{
  // Gradually increase the LED brightness.
  for (int brightness = 0;
       brightness <= maximumBrightness;
       brightness++) {

    setLedBrightness(brightness);
    delay(fadeStepDelay);
  }

  // Gradually decrease the LED brightness.
  for (int brightness = maximumBrightness;
       brightness >= 0;
       brightness--) {

    setLedBrightness(brightness);
    delay(fadeStepDelay);
  }

  // Pause before starting the next fade cycle.
  delay(pauseDuration);
}