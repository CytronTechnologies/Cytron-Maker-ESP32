/*
  DESCRIPTION:
  Plays Twinkle Twinkle Little Star using the onboard buzzer.

  The melody repeats continuously.

  AUTHOR:
  Cytron Technologies Sdn Bhd

  WEBSITE:
  https://www.cytron.io

  EMAIL:
  support@cytron.io
*/

// Buzzer pin
const int buzzerPin = 26;

// Notes
const int noteC4 = 262;
const int noteD4 = 294;
const int noteE4 = 330;
const int noteF4 = 349;
const int noteG4 = 392;
const int noteA4 = 440;

// Melody
const int melody[] = {
  noteC4, noteC4, noteG4, noteG4,
  noteA4, noteA4, noteG4,

  noteF4, noteF4, noteE4, noteE4,
  noteD4, noteD4, noteC4,

  noteG4, noteG4, noteF4, noteF4,
  noteE4, noteE4, noteD4,

  noteG4, noteG4, noteF4, noteF4,
  noteE4, noteE4, noteD4,

  noteC4, noteC4, noteG4, noteG4,
  noteA4, noteA4, noteG4,

  noteF4, noteF4, noteE4, noteE4,
  noteD4, noteD4, noteC4
};

// Duration of each note.
// 4 = quarter note, 2 = half note.
const int noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 2
};

const int melodyLength =
  sizeof(melody) / sizeof(melody[0]);

// Play the melody.
void playMelody()
{
  const int tempo = 1000;

  for (int i = 0; i < melodyLength; i++) {
    int noteDuration = tempo / noteDurations[i];

    tone(buzzerPin, melody[i], noteDuration);

    delay(noteDuration);

    noTone(buzzerPin);

    // Short pause between notes.
    delay(noteDuration * 0.15);
  }
}


void setup()
{
  // Configure the buzzer pin.
  pinMode(buzzerPin, OUTPUT);
}


void loop()
{
  // Play the melody.
  playMelody();

  // Short pause before playing again.
  delay(1000);
}