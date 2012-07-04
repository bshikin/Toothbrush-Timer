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
 * This class is used to controll servo motor of the box
 *
 *  Created on: May 27, 2012
 *      Author: Basil Shikin
 */

#ifndef SERVOCONTROLLER_H_
#define SERVOCONTROLLER_H_

#include "Arduino.h"
#include "Servo.h"

class ServoController
{
public:
    ServoController();

    void initialize( uint8_t servoPin, uint8_t powerPin);

    void ding();

    void reset();

private:
    uint8_t m_servoPin;
    uint8_t m_powerPin;

    Servo m_servo;
};

#endif /* SERVOCONTROLLER_H_ */
