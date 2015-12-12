#KeypadEvents

## What is this?
KeypadEvents is an Arduino library that watches the state of keys on a keypad connected to the Arduino and calls assigned callbacks when the key states change.

## Usage
1. Install the library by cloning it into your Arduino user library directory (`/Users/<name>/Documents/Arduino/libraries/` on OSX)
2. Include the KeypadEvents library:
`#include <KeypadEvents.h>`
3. Create a `KeypadEvents` object, initialize input pins (`init()`), assign handlers, and call `KeypadEvents::readEvents()` each loop:

```c++
KeypadEvents keyevents;

void key_down(char key) {
    Serial.print("Key down:");
    Serial.println(key);
}

void key_up(char key) {
    Serial.print("Key up:");
    Serial.println(key);
}

void key_pressed(char key) {
    Serial.print("Key pressed:");
    Serial.println(key);
}

void setup() {
    keyevents.init();
    keyevents.onKeyDown(key_down);
    keyevents.onKeyUp(key_up);
    keyevents.onKeyPressed(key_pressed);
}

void loop() {
    ...
    keyevents.readEvents();
}
```

## License
The MIT License (MIT)

Copyright © 2015 Casey Chance

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

