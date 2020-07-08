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

#include <mbed.h>
#include <Button.h>

// nucleo64 userbutton needs to be configured as FALL_TO_RISE
Button button(USER_BUTTON, FALL_TO_RISE);
DigitalOut led(LED1);

void onClick() {
  // toggle onboard led
  led != led;
}

void onLongClick() {
  // blink led once
  led = 0;
  wait_us(100000);
  led = 1;
  wait_us(100000);
  led = 0;
}

void onDoubleClick() {
  // blink led a few times
  for (int i = 0; i < 10; i++)
  {
    led = !led;
    wait_us(100000);
  }
  
}

int main() {
  // attach ISR for button click
  button.onClick(&onClick);

  // attach ISR for button double click
  button.onDoubleClick(&onDoubleClick);

  // attach ISR for button press
  button.onLongClick(&onLongClick);

  while(1) {
    // do nothing, everything is handled by interrupts
    sleep();
  }
}
