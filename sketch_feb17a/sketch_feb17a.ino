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

#define KEY_ONE     0x04 /* 1 */
#define KEY_TWO     0x1F
#define KEY_THREE   0xE1
#define KEY_FOUR    0x21

#define PIN_ONE     4
#define PIN_TWO     5
#define PIN_THREE   6
#define PIN_FOUR    7

int leftShiftState = 1;

int state = 1;
int state1 = 1;
int state2 = 1;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  delay(200);

  pinMode(PIN_ONE, INPUT);
  pinMode(PIN_TWO, INPUT);
  pinMode(PIN_THREE, INPUT);
  pinMode(PIN_FOUR, INPUT);

  digitalWrite(PIN_ONE, 1);
  digitalWrite(PIN_TWO, 1);
  digitalWrite(PIN_THREE, 1);
  digitalWrite(PIN_FOUR, 1);
}

void loop()
{

  leftShiftState = digitalRead(PIN_ONE);

  state = digitalRead(PIN_TWO);
  if (state != 1) {
    buf[0] = modifier(leftShiftState);
    buf[2] = KEY_TWO;
    Serial.write(buf, 8);
    releaseKey();
    delay(200);
  }


  state2 = digitalRead(PIN_THREE);
  if (state2 != 1) {
    buf[0] = modifier(leftShiftState);
    buf[2] = KEY_ONE;
    Serial.write(buf, 8);
    releaseKey();
    delay(200);
  }

  state = digitalRead(PIN_FOUR);
  if (state != 1) {
    buf[0] = modifier(leftShiftState);
    buf[2] = KEY_FOUR;
    Serial.write(buf, 8);
    releaseKey();
    delay(200);
  }

}

void releaseKey()
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key
}

int modifier(int leftShiftState)
{
  if (leftShiftState != 1) {
    return 2;
  } else {
    return 0;
  }
}


