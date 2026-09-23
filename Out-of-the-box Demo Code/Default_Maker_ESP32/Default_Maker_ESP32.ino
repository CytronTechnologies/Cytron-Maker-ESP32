/*
  DESCRIPTION:
  Default demo program for the Cytron Maker ESP32 Rev 1.0.

  On startup, the LEDs run a chase animation while the buzzer plays
  a startup chime. Pressing the button reverses the LED animation
  direction and plays the chime again.

  The LED animation and chime use millis() so they can run at the
  same time without blocking each other.

  AUTHOR:
  Cytron Technologies Sdn Bhd

  WEBSITE:
  https://www.cytron.io

  EMAIL:
  support@cytron.io
*/

// LED pins
const int ledPins[] = {
  32, 33, 25, 27, 12, 13,
  23, 22, 21, 19, 18, 17, 16, 2
};

const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Button and buzzer pins
const int buttonPin = 4;
const int buzzerPin = 26;

// LED animation timing
const unsigned long ledInterval = 100;

// LED animation state
int currentLed = 0;
bool forwardDirection = true;
unsigned long lastLedUpdate = 0;

// Button debounce
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;

const unsigned long debounceDelay = 50;

// Startup chime
// Frequency 0 represents a rest.
const int chimeFrequencies[] = {
  262, 330, 392, 440, 494, 523,
  1047,
  0,
  1319, 1047, 1319,
  0,
  1047
};

const int chimeDurations[] = {
  140, 140, 140, 140, 140, 140,
  420,
  60,
  55, 55, 55,
  50,
  600
};

const int chimeLength =
  sizeof(chimeFrequencies) / sizeof(chimeFrequencies[0]);

// Chime playback state
int chimeIndex = 0;
bool chimePlaying = false;
unsigned long chimeNoteStart = 0;


// Start the startup chime from the beginning.
void startChime()
{
  chimeIndex = 0;
  chimePlaying = true;
  chimeNoteStart = millis();

  playCurrentNote();
}


// Update the chime without blocking the program.
void updateChime()
{
  if (!chimePlaying) {
    return;
  }

  if (millis() - chimeNoteStart >=
      (unsigned long)chimeDurations[chimeIndex]) {

    chimeIndex++;

    if (chimeIndex >= chimeLength) {
      noTone(buzzerPin);
      chimePlaying = false;
      return;
    }

    chimeNoteStart = millis();

    playCurrentNote();
  }
}


// Play the current chime note.
void playCurrentNote()
{
  if (chimeFrequencies[chimeIndex] == 0) {
    noTone(buzzerPin);
  }
  else {
    tone(
      buzzerPin,
      chimeFrequencies[chimeIndex],
      chimeDurations[chimeIndex]
    );
  }
}


// Update the LED chase animation without blocking the program.
void updateAnimation()
{
  if (millis() - lastLedUpdate < ledInterval) {
    return;
  }

  lastLedUpdate = millis();

  turnOffAll();
  digitalWrite(ledPins[currentLed], HIGH);

  if (forwardDirection) {
    currentLed++;

    if (currentLed >= ledCount) {
      currentLed = 0;
    }
  }
  else {
    currentLed--;

    if (currentLed < 0) {
      currentLed = ledCount - 1;
    }
  }
}


// Turn off all LEDs.
void turnOffAll()
{
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}


// Check the button and detect a button press.
void updateButton()
{
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // The button is active LOW because INPUT_PULLUP is used.
      if (buttonState == LOW) {
        forwardDirection = !forwardDirection;

        // Restart the chime from the beginning.
        startChime();
      }
    }
  }

  lastButtonState = reading;
}


void setup()
{
  // Configure the LED pins.
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Turn on the first LED immediately.
  digitalWrite(ledPins[currentLed], HIGH);

  // Configure the button.
  pinMode(buttonPin, INPUT_PULLUP);

  // Configure the buzzer.
  pinMode(buzzerPin, OUTPUT);

  // Start the startup chime.
  startChime();
}


void loop()
{
  updateButton();
  updateAnimation();
  updateChime();
}