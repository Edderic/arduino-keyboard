// Keyboard Matrix Tutorial Example
// baldengineer.com
// CC BY-SA 4.0

uint8_t buf[8] = {
0 }; /* Keyboard report buffer */

// JP1 is an input
byte rows[] = {2,3};
const int rowCount = sizeof(rows)/sizeof(rows[0]);

// JP2 and JP3 are outputs
byte cols[] = {8,9};
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];

#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D

int keyValues[2][2] = {
  { KEY_A, KEY_B },
  { KEY_C, KEY_D }
};

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
              buf[0] = 0;
              buf[2] = keyValues[colIndex][rowIndex];
              Serial.write(buf, 8);
              releaseKey();
              delay(200);
            }
        }
    }
}

void loop() {
    readMatrix();
    printMatrix();
}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}


