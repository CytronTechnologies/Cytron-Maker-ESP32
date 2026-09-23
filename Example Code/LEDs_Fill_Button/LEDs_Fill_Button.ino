/*
  DESCRIPTION:
  Sequential LED fill controlled by a button.

  On startup, only the first LED (pin 32) is on.
  Each button press turns on the next LED in sequence.
  Once all LEDs are on, the next press turns them all off.
  The following press starts the cycle again from the first LED.

  AUTHOR:
  Cytron Technologies Sdn Bhd

  WEBSITE:
  https://www.cytron.io

  EMAIL:
  support@cytron.io
*/

// LED pins in sequence
const int ledPins[] = {
  32, 33, 25, 27, 12, 13,
  23, 22, 21, 19, 18, 17, 16, 2
};

const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Button pin
const int buttonPin = 4;

// Number of LEDs currently turned on.
// 0 = all LEDs off
// ledCount = all LEDs on
int litCount = 1;

// Button debounce
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 50;


// Update the LEDs based on the current litCount.
void updateLeds()
{
  for (int i = 0; i < ledCount; i++) {
    if (i < litCount) {
      digitalWrite(ledPins[i], HIGH);
    }
    else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}


// Check the button and update the number of lit LEDs.
void updateButton()
{
  int reading = digitalRead(buttonPin);

  // Reset the debounce timer when the button state changes.
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check whether the button state has remained stable.
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Detect a button press.
      // The button is active LOW because INPUT_PULLUP is used.
      if (buttonState == LOW) {
        litCount++;

        // Start again from all LEDs off after all LEDs are on.
        if (litCount > ledCount) {
          litCount = 0;
        }

        updateLeds();
      }
    }
  }

  lastButtonState = reading;
}


void setup()
{
  // Configure the LED pins as outputs.
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Configure the button with the internal pull-up resistor.
  // The button should be connected between the pin and GND.
  pinMode(buttonPin, INPUT_PULLUP);

  // Show the initial state.
  // Only the first LED is turned on.
  updateLeds();
}


void loop()
{
  updateButton();
}