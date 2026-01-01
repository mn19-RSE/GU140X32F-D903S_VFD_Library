// Sketch designed to dsiplay a bitmap with the Adafruit GFC library in the form of a C array


#include <SPI.h>
#include "GUD900.h" // Library includes SPI

#define CS_PIN 24

GUD900 display(SPI, CS_PIN);


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

  // Draw bitmap at:
  // x = 0 pixels
  // y = 0 byte row (top of screen)
  display.drawBitmap(
    0,          // xDot
    0,          // yByte
    8,          // width (pixels)
    8,          // height (pixels)
    checker8x8
  );
}

void loop() {
  // Nothing here on purpose
}
