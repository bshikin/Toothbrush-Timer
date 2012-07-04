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
/*
 * ServoController.cpp
 *
 *  Created on: May 27, 2012
 *      Author: Basil Shikin
 */

#include "ServoController.h"


void ServoController::initialize( uint8_t servoPin, uint8_t powerPin )
{
    m_servoPin = servoPin;
    m_powerPin = powerPin;

    pinMode( m_powerPin, OUTPUT );
    reset();
}

void ServoController::ding()
{
    // Turn on servo
    digitalWrite( m_powerPin, LOW );
    delay( 200 );

    m_servo.attach(m_servoPin);

    m_servo.write(170);
    delay(100);
    m_servo.write(180);
    delay(100);

    m_servo.detach();

    // Turn off servo
    delay( 200 );
    digitalWrite( m_powerPin, HIGH );
}

void ServoController::reset()
{
    // Turn on servo
    digitalWrite( m_powerPin, LOW );
    delay( 500 );

    m_servo.attach(m_servoPin);
    while (!m_servo.attached() );

    m_servo.write(180);
    delay(1000);
    m_servo.detach();

    // Turn off servo
    delay( 200 );
    digitalWrite( m_powerPin, HIGH );
}

ServoController::ServoController() {}


