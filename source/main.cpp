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

#include "main.h"

extern "C" void __cxa_pure_virtual()
{
  cli();
  for (;;);
}

__extension__ typedef int __guard __attribute__((mode (__DI__)));

void * operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void * ptr)
{
    if (ptr)
        free(ptr);
}

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);}
void __cxa_guard_release (__guard *g) {*(char *)g = 1;}
void __cxa_guard_abort (__guard *) {}


// Pin mappings
#define PIN_L1   9
#define PIN_L2  10
#define PIN_L3  11
#define PIN_L4  3
#define PIN_L5  5
#define PIN_L6  6

#define PIN_SERVO_CONTROL  8
#define PIN_SERVO_POWER    2

#define PIN_SCALES_READING A5
#define PIN_SCALES_POWER   7

// Constants
#define LAMP_COUNT         6
#define DING_COUNT         4
#define WEIGHT_THRESHOLD   0.8
#define ANIMATION_DURATION 120000 // 2 minutes
#define TIME_INCREMENT     100
#define READ_SAMPLES       1000

// Objects
static LampController  s_lampController;
static ServoController s_servoController;
static double          s_lastReading;

// Common numbers
uint32_t dingInterval;
uint32_t lampInterval;
uint32_t dimIncrement;

double readWeight()
{
    // Turn on scales
    digitalWrite(PIN_SCALES_POWER, HIGH);

    // Read average value
    double total = 0;
    for (uint16_t i = 0; i < READ_SAMPLES; i++)
    {
        total += analogRead(PIN_SCALES_READING);
    }

    // Turn off scales
    digitalWrite(PIN_SCALES_POWER, LOW);

    return total / READ_SAMPLES;
}


void setup()
{
    // Setup sleep timer
    su_initialize();

    // Setup common numbers
    dingInterval  = ANIMATION_DURATION/DING_COUNT;
    lampInterval  = ANIMATION_DURATION/LAMP_COUNT;
    dimIncrement  = LAMP_MAX/(lampInterval/TIME_INCREMENT);

    // Initialize servo controller
    s_servoController.initialize( PIN_SERVO_CONTROL, PIN_SERVO_POWER );

    // Initialize lamp controller
    uint8_t lamps[LAMP_COUNT] = {PIN_L1, PIN_L2, PIN_L3, PIN_L4, PIN_L5, PIN_L6};
    s_lampController.initialize( lamps, LAMP_COUNT );
    s_lampController.playInitSequence();

    // Setup weight pin and read baseline weight
    pinMode(PIN_SCALES_POWER, OUTPUT);
    pinMode(PIN_SCALES_READING, INPUT);

    s_lastReading = readWeight();
}

void playAnimation()
{
    s_servoController.ding();
    s_lampController.turnAllOn();

    int32_t  timeRemaining = ANIMATION_DURATION;
    uint8_t  activeLamp = 0;
    uint16_t activeLampBrightness = LAMP_MAX;

    while (timeRemaining > 0)
    {
        if ( timeRemaining < ANIMATION_DURATION )
        {
            if (timeRemaining % dingInterval == 0)
            {
                s_servoController.ding();
            }

            if (timeRemaining % lampInterval == 0 )
            {
                s_lampController.turnOff(activeLamp);
                activeLamp += 1;

                activeLampBrightness = LAMP_MAX;
            }
        }

        // Update current lamp
        s_lampController.setBrightness(activeLamp, activeLampBrightness);
        activeLampBrightness -= dimIncrement;

        timeRemaining -= TIME_INCREMENT;

        delay( TIME_INCREMENT );
    }

    s_servoController.ding();
    s_lampController.turnAllOff();
}

void loop()
{
    double newReading = readWeight();
    if ( s_lastReading - newReading > WEIGHT_THRESHOLD )
    {
        playAnimation();
    }

    s_lastReading = newReading;
}

int main(void)
{
    // Initialize Arduino library
	init();

	// Setup ourselves
	setup();

	while (true)
	{
	    // Do the work
	    loop();

	    // Sleep
	    su_sleep(8);
	}

	return 0;
}
