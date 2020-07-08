#include <Button.h>

Button::Button(PinName pin, button_edge_order_t edgeOrder, PinMode mode) : buttonInput(pin, mode) {
    if (edgeOrder == RISE_TO_FALL) {
        // click starts with rising edge, ends with falling edge
        buttonInput.rise(callback(this, &Button::onButtonDown));
        buttonInput.fall(callback(this, &Button::onButtonRelease));
    }else{
        // click starts with falling edge, ends with rising edge
        buttonInput.fall(callback(this, &Button::onButtonDown));
        buttonInput.rise(callback(this, &Button::onButtonRelease));
    }
    
}


void Button::onButtonDown() {
    // start timer to measure how long the button is pressed
    pressTimer.start();
    buttonPressed = true;
}


void Button::onButtonRelease() {
    if (pressTimer.read_ms() >= DEFAULT_PRESS_THRESHHOLD){
        // long press
        onLongClickHandler();
    }else{
        // click

        if (previousClick) {
            // previos click withing double click time span -> its a double click
            onDoubleClickHandler();

            // stop timeout
            doubleClickTimeout.detach();
            previousClick = false;
        }else{
            //onClickHandler();

            // start double click timer
            previousClick = true;
            doubleClickTimeout.attach_us(callback(this, &Button::checkDoubleClick), DEFAULT_DOUBLE_CLICK_DELAY * 1000);
        }
        
    }

    // stop and reset timer
    pressTimer.stop();
    pressTimer.reset();
    buttonPressed = false;
}

void Button::checkDoubleClick() {
    // no second click in timeout, it was a single click
    onClickHandler(); 

    previousClick = false;
}
