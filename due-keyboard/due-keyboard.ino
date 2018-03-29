#include <Keyboard.h>

// Keyboard Matrix Tutorial Example
// baldengineer.com
// CC BY-SA 4.0

// JP1 is an input
byte rows[] = {2,3,4,5,6,7,8,9};
const int rowCount = sizeof(rows)/sizeof(rows[0]);

// JP2 and JP3 are outputs
byte cols[] = {22,24,26,28,30,32,34,36,38,40};
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];
#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D

int keyValues[8][10] = {
  {KEY_A, KEY_B, 'c', 'd', 'e' , 'f', 'g', 'h', 'i', 'j' },
  {KEY_C, KEY_D, 'm', 'n', 'o' , 'p', 'q', 'r', 's', 't' },
  {'u', 'v', 'w', 'x', 'y' , 'z', 'A', 'B', 'C', 'D' },
  {'E', 'F', 'G', 'H', 'I' , 'J', 'K', 'L', 'M', 'N' },
  {'O', 'P', 'Q', 'R', 'S' , 'T', 'U', 'V', 'W', 'X' },
  {'Y', 'z', '0', '1', '2' , '3', '4', '5', '6', '7' },
  {'8', '9', '-', '_', '?' , '?', '.', '>', ',', '<' },
  {'!', '@', '#', '$', '%' , '^', '&', '*', '(', ')' }
};

void setup() {
    // What is this number?

    for(int x=0; x<rowCount; x++) {
        pinMode(rows[x], INPUT);
    }

    for (int x=0; x<colCount; x++) {
        pinMode(cols[x], INPUT_PULLUP);
    }

    Keyboard.begin();
}

void readMatrix() {
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
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}

void printMatrix() {
    for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
        for (int colIndex=0; colIndex < colCount; colIndex++) {
            if (keys[colIndex][rowIndex] != 1) {
              Keyboard.press(keyValues[colIndex][rowIndex]);
            }
        }
    }

    Keyboard.releaseAll();
    delay(120);
}

void loop() {
    readMatrix();
    printMatrix();
}

