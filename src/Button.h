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

#ifndef MBED_BUTTON_H
#define MBED_BUTTON_H

#include <mbed.h>
#include <DebouncedIn.h>

#define DEFAULT_PRESS_THRESHHOLD 500
#define DEFAULT_DOUBLE_CLICK_DELAY 250

/**
 * Order of rising / falling edge that causes a click
 */
typedef enum button_edge_order {
    /* Button click is started by rising edge, ended by falling edge */
    RISE_TO_FALL,
    /* Button click is started by falling edge, ended by rising edge */
    FALL_TO_RISE
}button_edge_order_t;

/**
 * Driver for a button
 */
class Button
{    
public:
    /**
     * Constructor
     * @param pin the pin to which the button is connected to
     * @param edgeOrder the order of rising/falling edge that identifies a click
     * @param mode the pull up/down mode for the button
     */
    Button(PinName pin, button_edge_order_t edgeOrder, PinMode mode);

    /**
     * Constructor. The edge mode is set to RISE_TO_FALL
     * @param pin the pin to which the button is connected to
     * @param mode the pull up/down mode for the button
     */
    Button(PinName pin, PinMode mode) : Button(pin, RISE_TO_FALL, mode) {};

    /**
     * Constructor. The mode is set to PullNone
     * @param pin the pin to which the button is connected to
     * @param edgeOrder the order of rising/falling edge that identifies a click
     */
    Button(PinName pin, button_edge_order_t edgeOrder) : Button(pin, edgeOrder, PullNone) {};

    /**
     * Attaches an ISR for the button click event
     * @param clickHandler the function that will be called when the button is clicked
     */
    void onClick(Callback<void()> clickHandler) {onClickHandler = clickHandler;};

    /**
     * Attaches an ISR for the button long click event.
     * @param presskHandler the function that will be called when the button is pressed for a longer period of time (500ms by default)
     */
    void onLongClick(Callback<void()> presskHandler) {onLongClickHandler = presskHandler;};

    /**
     * Attaches an ISR for the button double click event.
     * @param doubleClickHandler the function that will be called when the button is double clicked within the double click delay period (250ms be default)
     */
    void onDoubleClick(Callback<void()> doubleClickHandler) {onDoubleClickHandler = doubleClickHandler;};

    /**
     * Returns whether the button is currently pressed.
     * @return true when the button is pressed, false otherwise
     */
    bool isPressed() {return buttonPressed;};
private:
    DebouncedIn buttonInput;
    LowPowerTimer pressTimer;
    LowPowerTimeout doubleClickTimeout;
    bool buttonPressed;
    bool previousClick;
    Callback<void()> onClickHandler;
    Callback<void()> onDoubleClickHandler;
    Callback<void()> onLongClickHandler;

    void checkDoubleClick();
    void onButtonDown();
    void onButtonRelease();
};

#endif