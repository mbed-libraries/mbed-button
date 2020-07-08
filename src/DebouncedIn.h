/*
MIT License

Copyright (c) 2020 Steffen S.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MBED_DEBOUNCEDIN_H
#define MBED_DEBOUNCEDIN_H

#include <mbed.h>

#define DEBOUNCE_TIME 0.01f // 10ms

/**
 * Provides a debounced input
 */
class DebouncedIn
{
public:
    /**
     * Constructor
     * @param pin the input pin to debounce
     * @param mode pull up / pull down mode for input pin
     */
    DebouncedIn(PinName pin, PinMode mode = PullNone);

    /**
     * Registers for the debounced rise event.
     * @param handler the function that is called on rise. Note that this is executed in an ISR
     */
    void rise(Callback<void()> handler);

    /**
     * Registers for the debounced fall event.
     * @param handler the function that is called on rise. Note that this is executed in an ISR
     */
    void fall(Callback<void()> handler);

    /**
     * Reads the current value of the input pin
     * @return the value of the input pin
     */
    int read();
private:
    InterruptIn input;
    LowPowerTimeout debounceRiseTimeout;
    LowPowerTimeout debounceFallTimeout;
    Callback<void()> riseHandler;
    Callback<void()> fallHandler;

    /* ISR handlers */
    void onInputRise();
    void onRiseTimeout();
    void onInputFall();
    void onFallTimeout();
};


#endif