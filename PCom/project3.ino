#include <FastLED.h>
#define LED_PIN1 6
#define LED_PIN2 5




#define NUM_LEDS 36
#define BRIGHTNESS_1  64
#define BRIGHTNESS_2  128
#define BRIGHTNESS_3  254
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

//bottom
int trigPin_D1 = 8;
int echoPin_D1 = 9;
int trigPin_D2 = 10;
int echoPin_D2 = 11;
int trigPin_D3 = 12;
int echoPin_D3 = 13;
//top
int trigPin_U3 = A5;
int echoPin_U3 = A4;
int trigPin_U2 = A3;
int echoPin_U2 = A2;
int trigPin_U1 = A1;
int echoPin_U1 = A0;

//bottom
long duration_1, distance_1, inches_1;
long duration_2, distance_2, inches_2;
long duration_3, distance_3, inches_3;
//top
long duration_4, distance_4, sdistance_4, inches_4;
long duration_5, distance_5, sdistance_5, inches_5;
long duration_6, distance_6, sdistance_6, inches_6;

//difference between each group
double firstDif;
double secondDif;
double thirdDif;

int ledTotal = 36;
int ledNum = 12;

double udDis = 17.78;
double d3Dis = 13;
double thres_2 = 13.72;
int errorRange = 3;

bool atFirst = false;
bool atSecond = false;
bool atThird = false;
bool atForth = false;
bool atFifth = false;
bool atSixth = false;

long myTime;
int timer = 0;
int brightness = 0;

bool pA = false;
bool pB = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin_D1, OUTPUT);
  pinMode(echoPin_D1, INPUT);
  pinMode(trigPin_D2, OUTPUT);
  pinMode(echoPin_D2, INPUT);
  pinMode(trigPin_D3, OUTPUT);
  pinMode(echoPin_D3, INPUT);

  pinMode(trigPin_U1, OUTPUT);
  pinMode(echoPin_U1, INPUT);
  pinMode(trigPin_U2, OUTPUT);
  pinMode(echoPin_U2, INPUT);
  pinMode(trigPin_U3, OUTPUT);
  pinMode(echoPin_U3, INPUT);

  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(leds2, NUM_LEDS);

  controlLed(0);
}

void loop() {
  myTime = millis();

  allSonar();

  if (distance_1 > 0 && distance_1 < udDis) atFirst = true;
  else atFirst = false;

  if (distance_2 > 0 && distance_2 < 13) atSecond = true;
  else atSecond = false;

  if (distance_3 > 0 && distance_3 < 13) atThird = true;
  else atThird = false;

  if (distance_4 > 0 && distance_4 < udDis) atForth = true;
  else atForth = false;

  if (distance_5 > 0 && distance_5 < udDis) atFifth = true;
  else atFifth = false;

  if (distance_6 > 0 && distance_6 < udDis) atSixth = true;
  else atSixth = false;

  //  Serial.print("First: ");
  //  Serial.println(atFirst);
  //
  //  Serial.print("Second: ");
  //  Serial.println(atSecond);
  //
  //  Serial.print("Third: ");
  //  Serial.println(atThird);
  //
  //  Serial.print("Forth: ");
  //  Serial.println(atForth);
  //
  //  Serial.print("Fifth: ");
  //  Serial.println(atFifth);
  //
  //  Serial.print("Sixth: ");
  //  Serial.println(atSixth);

  if (pA && pB) {
    samePipe();
    flowCondition();
  }
  else {
    single();
  }



  //controlLed(12);

  delay(100);

}

void firstSonar() {
  digitalWrite(trigPin_D1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_D1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D1, LOW);

  duration_1 = pulseIn(echoPin_D1, HIGH);
  distance_1 = duration_1 * 0.034 / 2;
  //  Serial.print("Distance 1: ");
  //  Serial.print(distance_1);
  //  Serial.println(" cm");
}

void secondSonar() {
  digitalWrite(trigPin_D2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_D2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D2, LOW);

  duration_2 = pulseIn(echoPin_D2, HIGH);
  distance_2 = duration_2 * 0.034 / 2;
  //  Serial.print("Distance 2: ");
  //  Serial.print(distance_2);
  //  Serial.println(" cm");
}

void thirdSonar() {
  digitalWrite(trigPin_D3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_D3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D3, LOW);

  duration_3 = pulseIn(echoPin_D3, HIGH);
  distance_3 = duration_3 * 0.034 / 2;
  //  Serial.print("Distance 3: ");
  //  Serial.print(distance_3);
  //  Serial.println(" cm");

}

void UfirstSonar() {
  digitalWrite(trigPin_U1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_U1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_U1, LOW);

  duration_4 = pulseIn(echoPin_U1, HIGH);
  sdistance_4 = duration_4 * 0.034 / 2;
  distance_4 = udDis - sdistance_4;
  //  Serial.print("Distance U1: ");
  //  Serial.print(distance_4);
  //  Serial.println(" cm");
}

void UsecondSonar() {
  digitalWrite(trigPin_U2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_U2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_U2, LOW);

  duration_5 = pulseIn(echoPin_U2, HIGH);
  sdistance_5 = duration_5 * 0.034 / 2;
  distance_5 = udDis - sdistance_5;
  //  Serial.print("Distance U2: ");
  //  Serial.print(distance_5);
  //  Serial.println(" cm");
}

void UthirdSonar() {
  digitalWrite(trigPin_U3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_U3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_U3, LOW);

  duration_6 = pulseIn(echoPin_U3, HIGH);
  sdistance_6 = duration_6 * 0.034 / 2;
  distance_6 = udDis - sdistance_6;
  //  Serial.print("Distance U3: ");
  //  Serial.print(distance_6);
  //  Serial.println(" cm");
}

void controlLed(int choice) {
  int enterTime = 0;
  //colorpalete
  //http://fastled.io/docs/3.1/struct_c_r_g_b.html
  if (choice == 12) {
    FastLED.setBrightness(250);
    for (int i = 0; i < ledTotal; i ++) {
      leds[i] = CRGB(0xFF4500);
      leds2[i] = CRGB(0xFF4500);
    }
    FastLED.show();
    delay(2000);           b                                                                                                                           
    controlLed(0);
  }
  if (choice == 13) {
    
  }

  //one player wait you here, breathe effect
  if (choice == 10) {

    for (int j = 0; j < 15; j++) {
      FastLED.setBrightness(4.0 * j);
      for (int i = 0; i < ledTotal; i ++) {
        //int b = map(i,0,ledNum,0,150);
        leds[i] = CRGB::Blue;
        FastLED.show();
      }
      delay(1);
    }
    //delay(5);
    for (int k = 15; k > 0; k--) {
      FastLED.setBrightness(4.0 * k);
      for (int i = 0; i < ledTotal; i ++) {
        //int b = map(i,0,ledNum,0,150);
        leds[i] = CRGB::Blue;
        FastLED.show();
      }
      delay(1);
    }
  }
  if (choice == 11) {
    for (int j = 0; j < 15; j++) {
      FastLED.setBrightness(4.0 * j);
      for (int i = 0; i < ledTotal; i ++) {
        //int b = map(i,0,ledNum,0,150);
        leds2[i] = CRGB::Blue;
        FastLED.show();
      }
      delay(1);
    }
    //delay(5);
    for (int k = 15; k > 0; k--) {
      FastLED.setBrightness(4.0 * k);
      for (int i = 0; i < ledTotal; i ++) {
        //int b = map(i,0,ledNum,0,150);
        leds2[i] = CRGB::Blue;
        FastLED.show();
      }
      delay(1);
    }
  }
  //all dark
  if (choice == 0) {
    for (int i = 0; i < ledTotal; i ++) {
      leds[i] = CRGB(0, 0, 0);
      leds2[i] = CRGB(0, 0, 0);
      FastLED.show();
    }
  }
}

void flow (bool L) {
  if (L) {
    CylonBounceL(0, 0, 0xff, 2, 40, 40);
    delay(200);
    controlLed(0);
  }
  else {
    CylonBounceR(0, 0, 0xff, 2, 40, 40);
    delay(200);
    controlLed(0);
  }
}


void CylonBounceR(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  FastLED.setBrightness(255);
  for (int i = 0; i < ledTotal ; i ++) {
    leds[i] = CRGB(0, 0, 0);
    leds2[i] = CRGB(0, 0, 0);
    FastLED.show();
  }
  int k = 23;
  for (int i = 0; i < ledNum - EyeSize; i++) {
    leds[i] = CRGB(red / 30, green / 30, blue / 30);
    leds[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds[k] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds2[k] = CRGB(red / 30, green / 30, blue / 30);

    for (int j = 1; j <= EyeSize; j++) {
      leds[i + j] = CRGB(red, green, blue);
      leds[i + 24 + j] = CRGB(red, green, blue);
      leds[k - j] = CRGB(red, green, blue);
      leds2[i + j] = CRGB(red, green, blue);
      leds2[i + 24 + j] = CRGB(red, green, blue);
      leds2[k - j] = CRGB(red, green, blue);
      delay(SpeedDelay);
    }

    leds[i] = CRGB(red / 30, green / 30, blue / 30);
    leds[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds[k] = CRGB(red / 30, green / 30, blue / 30);

    leds2[i] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds2[k] = CRGB(red / 30, green / 30, blue / 30);
    FastLED.show();
    delay(SpeedDelay);
    k --;
  }
}

void CylonBounceL(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  FastLED.setBrightness(255);
  for (int i = 0; i < ledTotal ; i ++) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
  }
  int k = 12;
  for (int i = ledNum - EyeSize + 1; i > 0 ; i--) {
    leds[i] = CRGB(red / 30, green / 30, blue / 30);
    leds[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds[k] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds2[k] = CRGB(red / 30, green / 30, blue / 30);

    for (int j = 1; j <= EyeSize; j++) {
      leds[i - j] = CRGB(red, green, blue);
      leds[i + 24 - j] = CRGB(red, green, blue);
      leds[k + j] = CRGB(red, green, blue);
      leds2[i - j] = CRGB(red, green, blue);
      leds2[i + 24 - j] = CRGB(red, green, blue);
      leds2[k + j] = CRGB(red, green, blue);
      delay(SpeedDelay);
    }

    leds[i] = CRGB(red / 30, green / 30, blue / 30);
    leds[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds[k] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i] = CRGB(red / 30, green / 30, blue / 30);
    leds2[i + 24] = CRGB(red / 30, green / 30, blue / 30);
    leds2[k] = CRGB(red / 30, green / 30, blue / 30);
    FastLED.show();
    delay(SpeedDelay);
    k ++;
  }
}




void allSonar() {
  firstSonar();
  delay(50);
  secondSonar();
  delay(50);
  thirdSonar();
  delay(50);
  UfirstSonar();
  delay(50);
  UsecondSonar();
  delay(50);
  UthirdSonar();
  delay(50);

  firstDif = distance_1 - distance_4;
  secondDif = distance_2 - distance_5;
  thirdDif = distance_3 - distance_6;

  //  Serial.print("First Dif: ");
  //  Serial.print(firstDif);
  //  Serial.println(" cm");
  //  Serial.print("Second Dif: ");
  //  Serial.print(secondDif);
  //  Serial.println(" cm");
  //  Serial.print("Third Dif: ");
  //  Serial.print(thirdDif);
  //  Serial.println(" cm");
}

void flowCondition() {
  int j = 4;
  bool l = true;
  bool r = false;

  if (atFirst && atSixth) {
    flow(r);
  }
  if (atForth && atThird) {
    flow(l);
  }
}

//！！！！map一下亮度，中间亮，两头暗
void samePipe() {
  if (firstDif > -3 && firstDif < 3) {
    controlLed(12);
    Serial.println("1");
    delay(800);
    controlLed(0);
  }
  if (secondDif > -3 && secondDif < 3) {
    controlLed(12);
    Serial.println("2");
    //    delay(800);
    //    controlLed(0);
  }
  if (thirdDif > -3 && thirdDif < 3) {
    controlLed(12);
    Serial.println("3");
    //    delay(800);
    //    controlLed(0);
  }
}

void single() {
  if (atFirst || atSecond || atThird) {
    if (!atForth || !atFifth || !atSixth) {
      controlLed(10);
      controlLed(0);

      if (!pA) pA = true;
    }
  }

  if (!atFirst || !atSecond || !atThird) {
    if (atForth || atFifth || atSixth) {
      controlLed(11);
      controlLed(0);
      if (!pB) pB = true;
    }
  }
}
