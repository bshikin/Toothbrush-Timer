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
 * This class is used to detect various notes. Guaranteed detection range is from C3 to C6.
 *
 *  Created on: Jan 29, 2012
 *      Author: Basil Shikin
 */

#ifndef LampController_H_
#define LampController_H_

#include "Arduino.h"

#define LAMP_MAX           160


class LampController
{
public:
	/**
	 * Create a new controller.
	 */
	LampController();

	/**
	 * Initialize note controller.
	 *
	 *     lampPins  Array with lamp
	 *     lampCount Number of lamps in the array
	 */
	void initialize( uint8_t * lampPins, uint8_t lampCount );

	/**
	 * Play starting sequence of lamps.
	 */
	void playInitSequence();

	/**
	 * Turn all lamps on
	 */
	void turnAllOn();

	/**
	 * Turn all lamps on
	 */
	void turnAllOff();

	/**
	 * Turn off a given lamp
	 *
	 *    lampNo Index of the lamp to turn off
	 */
	void turnOff(uint8_t lampNo);

	/**
	 * Update brightness of a current lamp
	 *
	 *    lampNo Index of the lamp to update
	 */
	void setBrightness(uint8_t lampNo, uint16_t factor);

	~LampController();

private:
	uint8_t * m_lampPins;
	uint8_t   m_lampCount;

	bool isPwm( uint8_t lampNo );
};

#endif /* LampController_H_ */
