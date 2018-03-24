/**
* Arduino USB HID Keyboard Demo
* Keys 1, 2, 3 and 4 on pins 4, 5, 6 and 7
*
* @info check details on my website
* @link http://blog.realhe.ro
*/
uint8_t buf[8] = {
0 }; /* Keyboard report buffer */

/*
    bit 0: left control
    bit 1: left shift
    bit 2: left alt
    bit 3: left GUI (Win/Apple/Meta key)
    bit 4: right control
    bit 5: right shift
    bit 6: right alt
    bit 7: right GUI
*/

// Modifier values
#define KEY_LEFT_CONTROL  0xE0
#define KEY_LEFT_SHIFT    0xE1
#define KEY_LEFT_ALT      0xE2
#define KEY_LEFT_GUI      0xE3
#define KEY_RIGHT_CONTROL 0xE4
#define KEY_RIGHT_SHIFT   0xE5
#define KEY_RIGHT_ALT     0xE6
#define KEY_RIGHT_GUI     0xE7

// Order matters
// Modifier pins
#define PIN_LEFT_CONTROL  2
#define PIN_LEFT_SHIFT    3
#define PIN_LEFT_ALT      4
#define PIN_LEFT_GUI      5
#define PIN_RIGHT_CONTROL 6
#define PIN_RIGHT_SHIFT   7
#define PIN_RIGHT_ALT     8
#define PIN_RIGHT_GUI     9

// TODO: w
// Non modifier values
#define KEYBOARD_7_AND_AMPERSAND  0x24

// Non modifier pin numbers
#define PIN_KEYBOARD_7_AND_AMPERSAND  10

int modifierInputs[] = {
  PIN_LEFT_CONTROL,
  PIN_LEFT_SHIFT,
  PIN_LEFT_ALT,
  PIN_LEFT_GUI,
  PIN_LEFT_CONTROL,
  PIN_LEFT_SHIFT,
  PIN_LEFT_ALT,
  PIN_LEFT_GUI,
};

int modifierValues[] = {
  KEY_LEFT_CONTROL,
  KEY_LEFT_SHIFT,
  KEY_LEFT_ALT,
  KEY_LEFT_GUI,
  KEY_LEFT_CONTROL,
  KEY_LEFT_SHIFT,
  KEY_LEFT_ALT,
  KEY_LEFT_GUI,
};

int regularInputs[] = {
  PIN_KEYBOARD_7_AND_AMPERSAND
};

int regularValues[] = {
  KEYBOARD_7_AND_AMPERSAND
};

int numModifierInputs = sizeof(modifierInputs) / sizeof(int);
int numRegularInputs = sizeof(regularInputs) / sizeof(int);

int modifierStates[8];
int regularStates[100];


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  delay(200);

  for(int i = 0; i < numModifierInputs; i++) {
    pinMode(modifierInputs[i], INPUT);
    digitalWrite(modifierInputs[i], 1);
  }

  for(int i = 0; i < numRegularInputs; i++) {
    pinMode(regularInputs[i], INPUT);
    digitalWrite(regularInputs[i], 1);
  }
}

void loop()
{

  // modifiers don't need to send info right away
  // others need to send info
  for(int i = 0; i < numModifierInputs; i++) {
    modifierStates[i] = digitalRead(modifierInputs[i]);
  }

  int modifierDecimal = getModifierDecimal();

  for(int i = 0; i < numRegularInputs; i++) {
    regularStates[i] = digitalRead(regularInputs[i]);

    if (regularStates[i] != 1) {
      buf[0] = modifierDecimal; // debug
      buf[2] = regularValues[i];
      Serial.write(buf, 8);
      releaseKey();
      delay(200);
    }
  }
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}

// Get the combination of modifier values, distilled into a single number
int getModifierDecimal()
{

  int total = 0;
  int multiplier = 1;

  for(int i = 0; i < numModifierInputs; i++) {
    if (i != 0) {
      multiplier *= 2;
    }

    if (modifierStates[i] != 1) {
      total += multiplier;
    }
  }

  return total;
}


