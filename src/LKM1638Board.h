/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file LKM1638Board.h
 * \brief JY-LKM1638 board v1.1 library for Arduino
 * \details
 *   Source:         https://github.com/Erriez/ErriezTM1638
 *   Source:         https://github.com/Erriez/ErriezLKM1638
 *   Documentation:  https://erriez.github.io/ErriezLKM1638
 */

#ifndef LKM1638_BOARD_H__
#define LKM1638_BOARD_H__

#include <Arduino.h>

#include <TM1638.h>

#define NUM_COLOR_LEDS    8 //!< Number of dual color LED's
#define NUM_DIGITS        8 //!< Number of digits

#define SEGMENTS_OFF      0b00000000 //!< 7-sgement digit all LED's off
#define SEGMENTS_MINUS    0b01000000 //!< 7-sgement digit minus character
#define SEGMENTS_DEGREE   0b01100011 //!< 7-sgement digit degree symbol
#define SEGMENTS_C        0b00111001 //!< 7-sgement digit Celsius symbol

#if (NUM_COLOR_LEDS > 8)
#error "Too many LED's. This won't fit in a 8-bit variable"
#endif

/*!
 * \brief Dual color LED
 */
typedef enum {
    LedOff = 0,
    LedRed = 1,
    LedGreen = 2
} LedColor;


/*!
 * \brief LKM1638Board class, derived from TM1638 library
 */
class LKM1638Board : public TM1638
{
public:
    // Constructor with 3 pins
    LKM1638Board(uint8_t clkPin, uint8_t dioPin, uint8_t stbPin);

    // Get buttons
    virtual uint8_t getButtons();

    // Turn all LED's off
    virtual void clear();

    // Set dual color LED's
    virtual void setColorLED(uint8_t led, LedColor color);
    virtual void colorLEDsOn(uint8_t leds, LedColor color);
    virtual void colorLEDsOff(uint8_t leds);

    // Refresh 7-segment display
    virtual void refresh();

    // Control 7-segment dots
    virtual void dotOn(uint8_t pos);
    virtual void dotOff(uint8_t pos);
    virtual void setDots(uint8_t dots);

    // Set/get position for print functions
    virtual void setPrintPos(uint8_t pos);
    virtual uint8_t getPrintPos();

    // Write
    virtual void setSegmentsDigit(uint8_t pos, uint8_t leds);
    virtual void setDigit(uint8_t pos, uint8_t digit);

    // Notes:  Overloaded functions with default arguments are not allowed, so
    // create multiple functions with different number of arguments.

    // Display unsigned value 8, 16 or 32-bit with optional padding
    virtual void print(uint8_t value);
    virtual void print(uint8_t value, uint8_t radius);
    virtual void print(uint8_t value, uint8_t radius, uint8_t maxDigits);
    virtual void print(uint8_t value, uint8_t radius, uint8_t maxDigits, uint8_t pad);

    virtual void print(uint16_t value);
    virtual void print(uint16_t value, uint8_t radius);
    virtual void print(uint16_t value, uint8_t radius, uint8_t maxDigits);
    virtual void print(uint16_t value, uint8_t radius, uint8_t maxDigits, uint8_t pad);

    virtual void print(unsigned long value);
    virtual void print(unsigned long value, uint8_t radius);
    virtual void print(unsigned long value, uint8_t radius, uint8_t maxDigits);
    virtual void print(unsigned long value, uint8_t radius, uint8_t maxDigits, uint8_t pad);

    // Display signed value 8, 16 or 32-bit
    virtual void print(int8_t value);
    virtual void print(int8_t value, uint8_t radius);
    virtual void print(int8_t value, uint8_t radius, uint8_t maxDigits);

    virtual void print(int16_t value);
    virtual void print(int16_t value, uint8_t radius);
    virtual void print(int16_t value, uint8_t radius, uint8_t maxDigits);

    virtual void print(long value);
    virtual void print(long value, uint8_t radius);
    virtual void print(long value, uint8_t radius, uint8_t maxDigits);

protected:
    uint8_t _leds[NUM_DIGITS];  //!< LED digits
    uint8_t _pos;               //!< Print position
    uint8_t _dots;              //!< Dot LED's

    virtual void writeDigit(uint8_t pos);
    virtual void writeUnsignedValue(uint32_t value, uint8_t radius, uint8_t maxDigits,
                                    uint8_t pad);
    virtual void writeSignedValue(int32_t value, uint8_t radius, uint8_t maxDigits);
    virtual uint8_t getNumDigits(uint32_t value, uint8_t radius);
    virtual void displayOverflow(uint8_t numDigits);

    // Swap bits and bytes
    virtual uint8_t swapBits(uint8_t data);
    virtual uint8_t swapPos(uint8_t pos);
    virtual uint8_t swapLeds(uint8_t led);
};

#endif // LKM1638_BOARD_H__
