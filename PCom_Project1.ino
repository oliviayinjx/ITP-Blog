#include "Servo.h"
#include "pitches.h"

//Lose tune
const int loseMelody[] = {
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_C4
};

//Win tune
const int winMelody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4
};

//Tune durations
const int durations[] = {
  2, 2, 4, 8, 8, 8
};

//Declare LED pins
const int greenLED = 2;
const int redLED = 3;
const int yellowLED = 4;
const int blueLED = 5;

//Declare button pins
const int greenButton = 6;
const int redButton = 7;
const int yellowButton = 8;
const int blueButton = 9;

//LED number pins
const int a = 21;
const int b = 20;
const int c = 19;
const int d = 17;
const int e = 16;
const int f = 10;
const int g = 11;
const int dp = 18;

//Declare servo
Servo servoMotor;
const int servoPin = 12;

//Detect button press
const int BUTTONPRESS = 50; //minimum length for a press in ms
long pressTime = 0; //Track press time

//Declare last button states of each button
int lastGreenButtonState = LOW;
int lastRedButtonState = LOW;
int lastYellowButtonState = LOW;
int lastBlueButtonState = LOW;

bool playerTurn = false; //State of game
int playerLED = 0; //Player's choice
int randLED = 0; //Game's choice

int LEDList[100]; //Array of random LEDs
int score = 0; //Current score/level or index of array
int check = 0; //Check variable

int onTime = 500; //LED on time

void setup() {

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  pinMode(greenButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(blueButton, INPUT);

  pinMode(12, OUTPUT);

  randomSeed(analogRead(A1));
  Serial.begin(9600);

  clearDisplay();
  display0();
  startUp();
  servoMotor.attach(servoPin);//servo pin is 12
}

void loop() {

  //GAME TURN
  if (playerTurn == false) {
    switch (score) {
      case 2: onTime = 300; break;
      case 4: onTime = 200; break;
      case 7: onTime = 125; break;
      case 9: onTime = 75; break;
    }

    delay(1000); //pause after player turn
    randLED = random(1, 5); //random number 1 - 4
    Serial.print("randLED: ");
    Serial.println(randLED);
    LEDList[score] = randLED; //add number to list
    //light LEDs corresponding to the numbers in the list
    for (int i = 0; i <= score; i++) {
      switch (LEDList[i]) {
        case 1:   digitalWrite(greenLED, HIGH); tone(A0, 440, onTime); break;
        case 2:   digitalWrite(redLED, HIGH); tone(A0, 480, onTime); break;
        case 3:   digitalWrite(yellowLED, HIGH); tone(A0, 520, onTime); break;
        case 4:   digitalWrite(blueLED, HIGH); tone(A0, 560, onTime); break;
      }
      delay(onTime);
      allOff();
      delay(onTime);
    }
    playerTurn = true; //end of game turn
  }

  //PLAYER TURN
  if (playerTurn == true) {
    int greenButtonState = digitalRead(greenButton);
    if (greenButtonState != lastGreenButtonState) {
      playerLED = 1;
      buttonPress(greenButtonState, greenLED);
      //tone(A0, 440, 500);
      lastGreenButtonState = greenButtonState;
      //Serial.println(lastGreenButtonState);
    }

    int redButtonState = digitalRead(redButton);
    if (redButtonState != lastRedButtonState) {
      playerLED = 2;
      buttonPress(redButtonState, redLED);
      //tone(A0, 480, 500);
      lastRedButtonState = redButtonState;
      //Serial.println(lastRedButtonState);
    }

    int yellowButtonState = digitalRead(yellowButton);
    if (yellowButtonState != lastYellowButtonState) {
      playerLED = 3;
      buttonPress(yellowButtonState, yellowLED);
      //tone(A0, 520, 500);
      lastYellowButtonState = yellowButtonState;
      //Serial.println(lastYellowButtonState);
    }

    int blueButtonState = digitalRead(blueButton);
    if (blueButtonState != lastBlueButtonState) {
      playerLED = 4;
      buttonPress(blueButtonState, blueLED);
      //tone(A0, 560, 500);
      lastBlueButtonState = blueButtonState;
      //Serial.println(lastBlueButtonState);
    }
  }
}

//Manage a button press
void buttonPress(int buttonState, int LED) {
  if (buttonState == HIGH) { //If new state is high
    pressTime = millis(); //Store time
  }
  if (buttonState == LOW) { //If new sate is low after being high
    long holdTime = millis() - pressTime; //Calculate hold time
    if (holdTime > BUTTONPRESS) { //If hold time > 50 ms it is a press
      //Light chosen LED
      digitalWrite(LED, HIGH);

      //when the light's on, speaker makes sound
      //if change the tone, remember change this:
      int toneLevel = 400 + ((LED-1) * 40);
      Serial.print("Tone Level: ");
      Serial.println(toneLevel);
      tone(A0, toneLevel, onTime);
      delay(onTime);
      
      digitalWrite(LED, LOW);

      //Check player choice against game List
      if (playerLED != LEDList[check]) {
        lose();
        delay(1000);
        restartGame();
      }
      //If check is equal to the max index in the list,
      //All player choices were checked against game
      else if (check == score) {
        score++; //Increment index to store another LED
        clearDisplay();
        displayNumber(score);
        if (score == 10) {
          win();
          delay(1000);
          restartGame();
        }
        else{
          playerTurn = false; //player turn is over
          check = 0; //restart the check for the next round
        }
      }
      else {
        check++; //Increment the check
      }
    }
  }
}


//Turn all LEDs on
void allOn() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(blueLED, HIGH);
}

//Turn all LEDs off
void allOff() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
}

void lose() {
  tone(A0, NOTE_C4, 1500);
  for (int i = 0; i < 6; i++) {
    allOn();
    delay(125);
    allOff();
    delay(125);
  }
  playMelody(loseMelody, durations);
}

void win(){
  servoMotor.write(179);
  playMelody(winMelody, durations);
}

void restartGame() {
  Serial.println("restart");
  onTime = 500;
  check = 0;
  score = 0;
  clearDisplay();
  display0();
  randomSeed(analogRead(A1));
  startUp();
  playerTurn = false;
}

void startUp() {
  servoMotor.write(0);
  digitalWrite(greenLED, HIGH); tone(A0, 440, 500);
  delay(500);
  allOff();
  digitalWrite(redLED, HIGH); tone(A0, 480, 500);
  delay(500);
  allOff();
  digitalWrite(yellowLED, HIGH); tone(A0, 520, 500);
  delay(500);
  allOff();
  digitalWrite(blueLED, HIGH); tone(A0, 560, 500);
  delay(500);
  allOff();
  allOn(); tone(A0, 880, 500);
  delay(500);
  allOff();
  delay(50);
}

void displayNumber( int currentScore) {
  Serial.print("current digit: ");
  Serial.println(currentScore);

  if (currentScore == 1) {
    display1();
  }
  else if (currentScore == 2) {
    display2();
  }
  else if (currentScore == 3) {
    display3();
  }
  else if (currentScore == 4) {
    display4();
  }
  else if (currentScore == 5) {
    display5();
  }
  else if (currentScore == 6) {
    display6();
  }
  else if (currentScore == 7) {
    display7();
  }
  else if (currentScore == 8) {
    display8();
  }
  else if (currentScore == 9) {
    display9();
  }
  else if (currentScore == 0) {
    display0();
  }


}

//display number 1
void display1(void)
{
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);
}
//display number2
void display2(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(dp, LOW);
}
// display number3
void display3(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}
// display number4
void display4(void)
{
  digitalWrite(f, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);

}
// display number5
void display5(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(dp, LOW);
}
// display number6
void display6(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(dp, LOW);
}
// display number7
void display7(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(dp, LOW);
}
// display number8
void display8(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(dp, LOW);
}
void clearDisplay(void)
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(g, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(dp, LOW);
}
void display9(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(dp, LOW);
}
void display0(void)
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(dp, LOW);
}

void playMelody(const int melody[], const int noteDurations[]){
  for (int thisNote = 0; thisNote < 6; thisNote++) {
    if(thisNote % 2 == 0){
      allOn();
      clearDisplay();
    }
    else{
      allOff();
      display8();
    }
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(A0, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(A0);
  }
}
