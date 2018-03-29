// Keyboard Matrix Tutorial Example
// baldengineer.com
// CC BY-SA 4.0

uint8_t buf[8] = {
0 }; /* Keyboard report buffer */

// JP1 is an input
byte rows[] = {2,3};
const int rowCount = sizeof(rows)/sizeof(rows[0]);

// JP2 and JP3 are outputs
byte cols[] = {22,24};
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];
byte prevKeys[colCount][rowCount];

int sameAsPrevCounter = 0;
boolean aKeyHasBeenPressed;

#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D

int keyValues[2][2] = {
  { KEY_A, KEY_B },
  { KEY_C, KEY_D }
};

int countSameKeyPresses = 0;

void setup() {
    // What is this number?

    Serial.begin(9600);
    // Serial.begin(115200);

    for(int x=0; x<rowCount; x++) {
        pinMode(rows[x], INPUT);
    }

    for (int x=0; x<colCount; x++) {
        pinMode(cols[x], INPUT_PULLUP);
    }

    for (int colIndex=0; colIndex < colCount; colIndex++) {
        for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
            prevKeys[colIndex][rowIndex] = 1;
        }
    }
}

void readMatrix() {
    // check to see if the new matrix is the same as the old. Initialize to
    // true in the beginning of a full pass in the matrix.

    // possible for a aKeyHasBeenPressed to be true even though one is not
    // clicking on anything if there's a short in the circuit

    boolean sameAsPrev = true;
    aKeyHasBeenPressed = false;

    // iterate the columns
    for (int colIndex=0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        byte curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);

        // row: interate through the rows
        for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
            byte rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            keys[colIndex][rowIndex] = digitalRead(rowCol);
            if (keys[colIndex][rowIndex] == prevKeys[colIndex][rowIndex]) {
              sameAsPrev = sameAsPrev && true;
            }

            if (keys[colIndex][rowIndex] != 1) {
              aKeyHasBeenPressed = aKeyHasBeenPressed || true;
            }

            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }

    if (sameAsPrev && aKeyHasBeenPressed) {
      countSameKeyPresses += 1;
    } else {
      countSameKeyPresses = 0;
    }
}

void printMatrix() {
    byte collectionRegularPressedKeys[6];
    byte pressedKeysCount = 0;

    for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
        for (int colIndex=0; colIndex < colCount; colIndex++) {
            if (keys[colIndex][rowIndex] != 1) {
              collectionRegularPressedKeys[pressedKeysCount] = keyValues[colIndex][rowIndex];
              pressedKeysCount += 1;

            }
        }
    }

    // TODO: calculate modifier keys
    buf[0] = 0;

    byte maxPressedKeysPossible = 6;

    for (int i = 0; i < maxPressedKeysPossible; i++) {
      buf[2+i] = collectionRegularPressedKeys[i];
    }

    Serial.write(buf, 8);
    releaseKey();
}

void loop() {
    readMatrix();
    if (aKeyHasBeenPressed) {
      if ((countSameKeyPresses >= 1000 && countSameKeyPresses % 100) || countSameKeyPresses == 0) {
        printMatrix();
      }
    }
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}


