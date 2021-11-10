#include <Encoder.h>
// 1 light
// 2 paper shredder
// 3 clock
// 4 safty box
const int encoder1PinA = 3;
const int encoder1PinB = 2;
const int encoder2PinA = 9;
const int encoder2PinB = 8;
const int encoder3PinA = 12;
const int encoder3PinB = 11;
const int encoder4PinA = 16;
const int encoder4PinB = 15;

//const int encoder1Switch = 21;
//const int encoder2Switch = 20;
const int encoder3Switch = 20;
const int encoder4Switch = 21;
int debounceDelay = 5;       // debounce time for the button in ms

//int switch1State = 0;
//int switch1Last = 0;
//int switch2State = 0;
//int switch2Last = 0;
int switch3State = LOW;
int switch3Last = LOW;
int switch4State = LOW;
int switch4Last = LOW;

long oldPos1  = 0;
long newPos1 = 0;
long oldPos2  = 0;
long newPos2 = 0;
long newPos3 = 0;
long newPos4 = 0;

long pressTime = 0; //Track press time
const int buttonPress = 50;

Encoder myEnc1(encoder1PinA, encoder1PinB);
Encoder myEnc2(encoder2PinA, encoder2PinB);
Encoder myEnc3(encoder3PinA, encoder3PinB);
Encoder myEnc4(encoder4PinA, encoder4PinB);

void setup() {
  Serial.begin(9600);

  newPos1 = 0;
  newPos2 = 0;
  newPos3 = 0;
  newPos4 = 0;
  pinMode(encoder3Switch, INPUT_PULLUP);
  pinMode(encoder4Switch, INPUT_PULLUP);
}

void loop() {
  //0.1 capacity
  newPos1 =  myEnc1.read();
  Serial.print(newPos1);
  Serial.print(",");
  //  if (newPos1 != oldPos1) {
  //    oldPos1 = newPos1;
  //  }

  newPos2 =  myEnc2.read();
  Serial.print(newPos2);
  Serial.print(",");

  newPos3 =  myEnc3.read();
  Serial.print(newPos3);
  Serial.print(",");

  newPos4 =  myEnc4.read();
  Serial.print(newPos4);
  Serial.print(",");


  switch3State = digitalRead(encoder3Switch);
  Serial.print(switch3State);
  Serial.print(",");

  switch4State = digitalRead(encoder4Switch);
  Serial.println(switch4State);

}
