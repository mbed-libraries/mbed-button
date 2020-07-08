#include <DebouncedIn.h>

DebouncedIn::DebouncedIn(PinName pin, PinMode mode) : input(pin, mode) {}

int DebouncedIn::read() {
    return input.read();
}

void DebouncedIn::rise(Callback<void()> handler) {
    riseHandler = handler;
    
    if (handler) {
        input.rise(callback(this, &DebouncedIn::onInputRise));
    }else{
        // reset input rise handler and timeout
        input.rise(nullptr);
        debounceRiseTimeout.detach();
    }
    
}

void DebouncedIn::onInputRise() {
    // start debounce timeout
    debounceRiseTimeout.attach(callback(this, &DebouncedIn::onRiseTimeout), DEBOUNCE_TIME);
}

void DebouncedIn::onRiseTimeout() {
    if (input.read() && riseHandler) {
        // call if input still high and handler != null 
        riseHandler();
    }
}

void DebouncedIn::fall(Callback<void()> handler) {
    fallHandler = handler;

    if (handler) {
        input.fall(callback(this, &DebouncedIn::onInputFall));
    }else{
        // reset input fall handler and timeout
        input.rise(nullptr);
        debounceFallTimeout.detach();
    }
}

void DebouncedIn::onInputFall() {
    // start debounce timeout
    debounceFallTimeout.attach(callback(this, &DebouncedIn::onFallTimeout), DEBOUNCE_TIME);
}

void DebouncedIn::onFallTimeout() {
    if (!input.read() && fallHandler) {
        // call if input still low and handler != null
        fallHandler();
    }
}