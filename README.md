# NOTE:
This library is a learning experiment and does not currently work

# GU140X32F-D903S_VFD_Library
Modern Arduino library for the Noritake GU140X32F-D903S graphical VFD.
Controller is:
    7292ZA00
    R5F21368
        SDFP

## Scope:
The goal of this project is to create a custom library for the Noritake VFD. This will be a learning experience for learning how to write custom libraries for SPI devices. The end product should be compatible with Adafruit GFX and be able to detect the touch inputs built into the display.


## Steps:

1.  Read the datasheet like a product manager

Write down features, not bytes.

2.  Write the .h first

Even if it doesn’t compile yet.

3.  Implement one method at a time

Start with:

begin()

clear()

write()

4.  Test each command immediately

Don’t batch.

5.  Refactor

When you see repeated byte patterns → helper function.


1️⃣ Low-level SPI transport (easy)

You need functions like:

void writeCommand(uint8_t cmd);
void writeData(uint8_t data);


This is ~30–50 lines of code.

SPI on RP2350 is easy and well supported.

2️⃣ Display init sequence (easy–medium)

From the Noritake datasheet:

reset

brightness

display ON

addressing mode

Usually ~10–20 commands, written once.

This is much simpler than the official library.

3️⃣ Framebuffer (moderate)

Adafruit_GFX works like this:

You keep a RAM buffer

drawPixel() sets bits in that buffer

You periodically push the buffer to the display

For 140×32 monochrome:

140 × 32 = 4480 pixels
4480 / 8 = 560 bytes


That’s tiny.

4️⃣ Implement Adafruit_GFX hooks (very small)

Minimum required override:

void drawPixel(int16_t x, int16_t y, uint16_t color);


Optionally:

void display();  // push buffer to VFD


Adafruit_GFX does the rest.