#include <SPI.h>

#define CS_PIN     24   // change if needed
#define RESET_PIN  6    // MUST be wired
#define SPI_CLOCK  500000  // conservative

void select() {
  digitalWrite(CS_PIN, LOW);
}

void deselect() {
  digitalWrite(CS_PIN, HIGH);
}

void send(uint8_t b) {
  SPI.transfer(b);
}

void setup() {
  pinMode(CS_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);

  deselect();

  // ---- HARDWARE RESET ----
  digitalWrite(RESET_PIN, LOW);
  delay(20);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);

  // ---- SPI INIT ----
  SPI.begin();
  SPI.beginTransaction(SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0));

  // ---- SOFTWARE RESET ----
  select();
  send(0x1B);
  send(0x40);
  deselect();
  delay(20);

  // ---- CLEAR SCREEN ----
  select();
  send(0x0C);
  deselect();
  delay(20);

  // ---- ALL DOTS ON (SCREEN TEST) ----
  select();
  send(0x1F);
  send(0x28);
  send(0x61);
  send(0x40);
  send(0x03);  // ALL DOT ON
  deselect();
}

void loop() {}
