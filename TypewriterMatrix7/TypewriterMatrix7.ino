#include "Wire.h"

#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(0);
uint16_t letters[27][2] = {
  {8, 4}, //a *
  {5, 4}, //b *
  {7, 13}, //c
  {7, 4}, //d *
  {1, 9}, //e *
  {7, 9}, //f *
  {2, 9}, //g *
  {2, 4}, //h *
  {9, 9}, //i *
  {0, 13}, //j
  {6, 9}, //k *
  {3, 9}, //l *
  {9, 4}, //m *
  {9, 13}, //n
  {9, 10}, //o
  {2, 10}, //p
  {8, 10}, //q
  {7, 10}, //r
  {1, 4}, //s *
  {0, 10}, //t
  {9, 11}, //u
  {0, 4}, //v *
  {1, 10}, //w
  {1, 13}, //x
  {0, 9}, //y *
  {8, 13}, //z
  {6, 13} //space
};

volatile uint8_t state = 0;
volatile uint8_t count = 0;
int x;

volatile uint8_t cn1 = 0;
volatile uint8_t cn2 = 0;

void setup() {
  Serial.begin(115200);
   Serial.setTimeout(1);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(3, INPUT_PULLUP); //Sets pin 3 to input
  lcd.begin(16, 2);
 lcd.setBacklight(HIGH);
}

void loop() {
while (!Serial.available());
 x = Serial.read();
  int cn1 =  letters[x - 97][0];
int cn2 =  letters[x - 97][1];
 attachInterrupt(digitalPinToInterrupt(3), downTrigger, FALLING);
  //delay(300);

  switch (state) {

    case 0:
      attachInterrupt(digitalPinToInterrupt(3), downTrigger, FALLING);
      break;

    case 1:

      attachInterrupt(digitalPinToInterrupt(3), upTrigger, RISING);
      break;

    case 2:
      detachInterrupt(digitalPinToInterrupt(3));
      //Serial.print ("bye");

      digitalWrite(4, LOW);
      delayMicroseconds(1000);
      digitalWrite(4, HIGH);

      //Serial.print (cn3);
      state = 3;
      break;
    case 3:

      detachInterrupt(digitalPinToInterrupt(3));
      break;
  }
  Serial.print(x);
}
void upTrigger() {


  //Serial.print(x);
  if (x == cn1) {

    //Serial.print(x);
    x = 0;
    state = 2;

  }
  x = x + 1;
}
void downTrigger() {
lcd.setCursor(0, 0);
 lcd.print("hi");
  lcd.setCursor(0, 1);
lcd.print("hello");
  if (digitalRead(3) == LOW) {
 
    if (count++ < 25) {

      detachInterrupt(digitalPinToInterrupt(3));//called when downpulse is read on CN1

      if (cn1 == 0) {
        state = 2;
      } else {
        state = 1;
      }
    } else state = 3;

  }
}
