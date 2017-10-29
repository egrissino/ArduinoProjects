#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIN 6
#define NUMLEDS 8
#define LAYER 4
#define LAYERS 2
#define COLUM 2
#define COLUMS 4
#define MAX 10
#define RGB 3

#define BUFF_SIZE 64

#define DELAY 100

Adafruit_NeoPixel cube = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

int bottom[LAYER] = {0, 2, 4, 6};
int top[LAYER] = {1, 3, 5, 7};
int right[LAYER] = {2, 3, 6, 7};
int left[LAYER] = {0, 1, 4, 5};

int col_0[COLUM] = {0, 1};
int col_1[COLUM] = {2, 3};
int col_2[COLUM] = {4, 5};
int col_3[COLUM] = {6, 7};

int* colums[COLUMS] = {col_0, col_1, col_2, col_3};

int order1[LAYER] = {0, 1, 3, 2};
int order2[LAYER] = {7, 6, 4, 5};

int set = 0;
int link;

void setup() {
  cube.begin();
  
  Wire.begin(8);
  Serial.begin(9600);
}

void loop() {
//  switch (set) {
//    case 1:
//      redloop();
//      break;
//    case 2:
//      blueloop();
//      break;
//    default:
//      redloop();
//    break;
//  }

  colloop(set);

  if (getSerial()) {
    set = link - 48;
    Serial.println(set);
  }
  
}

bool getWire() {
  const int bytes = Wire.available();
  if ( bytes > 0) {
    byte msg[bytes] = {};

    for(int i = 0; i < bytes; i++) {
      msg[i] = Wire.read();
    }
    if (msg[0] == B0) {
      link = msg[0];
      return true;
    }
    else {
//      for (int i = 0; i < bytes; i ++) {
//        Serial.print(msg[i]);
//      }
      return false;
    }
  }
  else {
    return false;
  }
}

bool getSerial() {
  const int bytes = Serial.available();
  if ( bytes > 0) {
    byte msg[bytes] = {};

    for(int i = 0; i < bytes; i++) {
      msg[i] = Serial.read();
    }
    if (msg[0] > 48 && msg[0] < 58) {
      link = msg[0];
      return true;
    }
    else {
//      for (int i = 0; i < bytes; i ++) {
//        Serial.println(msg[i]);
//      }
      return false;
    }
  }
  else {
    return false;
  }
}

void redloop() {
  for (int i = 0; i < LAYER; i++) {
    cube.clear();
    for (int j = 0; j < LAYER; j++) {
      cube.setPixelColor(bottom[j], MAX, MAX, MAX);
      cube.setPixelColor(top[j], MAX, MAX, MAX);
    }
    cube.setPixelColor(order1[i], MAX, 0, 0);
    cube.setPixelColor(order2[i], MAX, 0, 0);
    cube.show();
    delay(DELAY);
  }
}

void blueloop() {
  for (int i = 0; i < LAYER; i++) {
    cube.clear();
    for (int j = 0; j < LAYER; j++) {
      cube.setPixelColor(bottom[j], MAX, 0, MAX);
      cube.setPixelColor(top[j], MAX, 0, MAX);
    }
    cube.setPixelColor(order1[i], MAX, 0, 0);
    cube.setPixelColor(order2[i], MAX, 0, 0);
    cube.show();
    delay(DELAY);
  }
}


void colloop(int col) {
  for (int i = 0; i < LAYER; i++) {
    cube.clear();
    for (int j = 0; j < LAYER; j++) {
      cube.setPixelColor(bottom[j], MAX, col * 28, MAX);
      cube.setPixelColor(top[j], MAX, col * 28, MAX);
    }
    cube.setPixelColor(order1[i], MAX, 0, 0);
    cube.setPixelColor(order2[i], MAX, 0, 0);
    cube.show();
    delay(DELAY);
  }
}
