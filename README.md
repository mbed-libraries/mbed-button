# Mbed Button
Button and debounced input driver for mbed

## How to use

### DebouncedIn
The class provides a way to debounce an arbitrary input. ISRs can be attached for rising and falling edges of the input.

```cpp
#include <mbed.h>
#include <DebouncedIn.h>

DebouncedIn input(USER_BUTTON);

void onRise(){
  // handle rising edge
}

void onFall() {
  // handle falling edge
}

int main() {
  // register ISRs
  input.rise(&onRise);
  input.fall(&onFall);
  
  while(1){
    // everything is handled by ISRs, so nothing to do here
  }
}
```

### Button
This class acts as a driver for pushbuttons that are attached to an input. It provides events for button single clicks, double clicks, and (long) button presses.

Create a button the following way
```cpp
Button button(USER_BUTTON, FALL_TO_RISE);
```

The second parameter specifies the the way a button click is detected. In this case a click is initiated with a falling edge and ended with a rising edge. By default, the other way around is used.

Attach ISRs to the button events
```cpp
  button.onClick(&onClick);
  button.onDoubleClick(&onDoubleClick);
  button.onLongClick(&onLongClick);
```
