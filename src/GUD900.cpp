#include "GUD900.h"

GUD900::GUD900(SPIClass &spi, uint8_t csPin)
: _spi(spi), _cs(csPin), _spiClock(1000000) {}

// Initialize SPI and display
bool GUD900::begin(uint32_t spiClock) {
    _spiClock = spiClock;

    pinMode(_cs, OUTPUT);
    deselect();

    _spi.begin();

    // Reset display
    select();
    _spi.transfer(0x1B);
    _spi.transfer(0x40);
    deselect();
    delay(10);

    // Clear screen
    select();
    _spi.transfer(0x0C);
    deselect();
    delay(10);

    return true;
}

// Lower CS and start SPI transaction
void GUD900::select() {
    _spi.beginTransaction(SPISettings(_spiClock, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs, LOW);
}

// Raise CS and end SPI transaction
void GUD900::deselect() {
    digitalWrite(_cs, HIGH);
    _spi.endTransaction();
}

// Move cursor to (xDot, yByte)
void GUD900::setCursor(uint16_t xDot, uint16_t yByte) {
    uint8_t cmd[] = {
        0x1F, 0x24,                     // Cursor move command
        (uint8_t)(xDot & 0xFF),         // x low
        (uint8_t)(xDot >> 8),           // x high
        (uint8_t)(yByte & 0xFF),        // y low
        (uint8_t)(yByte >> 8)           // y high
    };

    select();
    for (uint8_t b : cmd) _spi.transfer(b);
    deselect();
}

// Draw a bitmap at the cursor
void GUD900::drawBitmap(
    uint16_t xDot,
    uint16_t yByte,
    uint16_t width,
    uint16_t heightPixels,
    const uint8_t *data
) {
    uint16_t yBytes = (heightPixels + 7) / 8;

    // Move cursor first
    setCursor(xDot, yByte);

    uint8_t header[] = {
        0x1F, 0x28, 0x66, 0x11,        // Bit image display command
        (uint8_t)(width & 0xFF),
        (uint8_t)(width >> 8),
        (uint8_t)(yBytes & 0xFF),
        (uint8_t)(yBytes >> 8),
        0x01                            // g = fixed
    };

    select();

    for (uint8_t b : header) _spi.transfer(b);

    uint32_t count = (uint32_t)width * yBytes;
    while (count--) {
        _spi.transfer(*data++);
    }

    deselect();
}
