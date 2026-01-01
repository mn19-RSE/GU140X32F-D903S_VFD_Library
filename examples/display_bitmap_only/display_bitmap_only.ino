// Sketch designed to dsiplay a bitmap with the Adafruit GFC library in the form of a C array

#include <SPI.h>
#include "GUD900.h"

#define CS_PIN 25
GUD900 display(SPI, CS_PIN);

// 8x8 checker pattern
const uint8_t checker8x8[] = {
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101
};

void setup() {
  display.begin(1000000);  // 1 MHz SPI
  display.drawBitmap(0, 0, 8, 8, checker8x8);
}

void loop() {}
