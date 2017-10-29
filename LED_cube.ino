// This Number should match the number of LEDS in your cube
#define LEDS 4

// Dont touch this
#define BITS 24

// This is the pin on your arduino that is data out
#define OUT 6

bool data[LEDS][BITS] = { };

void setup() {
  // put your setup code here, to run once:
  pinMode(OUT, OUTPUT);

  for (int i = 0; i < LEDS; i++) {
    for (int j = 0; j < 8; j++) {
      data[i][j] = false;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < LEDS; i++){
    for (int j = 0; j < 24; j++) {
      if (data[i][j] == true) {
        writeOne(OUT);
      } else {
        writeZero(OUT);
      }
    }
  }
  delay(50);
}


void writeZero(int pin) {
  digitalWrite(pin, HIGH);
  delay(0.35);
  digitalWrite(pin, LOW);
  delay(0.8);
}

void writeOne(int pin) {
  digitalWrite(pin, HIGH);
  delay(0.7);
  digitalWrite(pin, LOW);
  delay(0.6);
}

