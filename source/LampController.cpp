/**
 * Copyright (c) 2012 Basil Shikin, BrushTimer Project
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "LampController.h"

LampController::LampController() {
}

LampController::~LampController() {
}

void LampController::initialize( uint8_t * lampPins, uint8_t lampCount )
{
    m_lampPins = (uint8_t *)malloc( sizeof(uint8_t) * lampCount );
    memcpy(m_lampPins, lampPins, lampCount);
    m_lampCount = lampCount;

    for ( uint8_t i = 0; i < m_lampCount; i++)
    {
        pinMode(m_lampPins[i], OUTPUT);
    }
}

void LampController::playInitSequence()
{
    turnAllOn();
    delay( 1000 );
    turnAllOff();
    delay(500);
}

void LampController::turnAllOn()
{
    for ( uint8_t i = 0; i < m_lampCount; i++)
    {
        digitalWrite( m_lampPins[i], HIGH);
    }
}

void LampController::turnAllOff()
{
    for ( uint8_t i = 0; i < m_lampCount; i++)
    {
        turnOff( i );
    }
}

void LampController::turnOff(uint8_t lampNo)
{
    digitalWrite( m_lampPins[lampNo], LOW);
}

void LampController::setBrightness(uint8_t lampNo, uint16_t factor)
{
    if (factor < 1)
    {
        turnOff( lampNo );
    }

    if ( isPwm(lampNo) )
    {
        analogWrite( m_lampPins[lampNo], factor);
    }
    else
    {
        digitalWrite( m_lampPins[lampNo], HIGH);
    }
}

bool LampController::isPwm( uint8_t lampNo )
{
    uint8_t pin = m_lampPins[lampNo];
    return pin == 3 ||
           pin == 5 ||
           pin == 6 ||
//           pin == 9 ||  DOES NOT WORK?
//           pin == 10 ||
           pin == 11;
}

