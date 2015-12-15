#include "KeypadEvents.h"

#include <string.h>

void noop(char) { }

char (KeypadEvents::buttons[4][4]) = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

KeypadEvents::KeypadEvents(int pins[]) : col1(ANALOG_COUNTS(R1)),
                                         col2(ANALOG_COUNTS(R2)),
                                         col3(ANALOG_COUNTS(R3)),
                                         col4(ANALOG_COUNTS(R4))
{
    memset(last_states, -1, sizeof(int)*4);

    /* Default handlers */
    handlers[KEY_UP].function = noop;
    handlers[KEY_DOWN].function = noop;
    handlers[KEY_PRESSED].function = noop;

    memcpy(pinmap, pins, 4 * sizeof(int));
}

void KeypadEvents::init() {
    /* Must be called from within `setup` function of sketch */
    pinMode(pinmap[0], INPUT);
    pinMode(pinmap[1], INPUT);
    pinMode(pinmap[2], INPUT);
    pinMode(pinmap[3], INPUT);
}

void KeypadEvents::onKeyDown(void (*function)(char)) {
    handlers[KEY_DOWN].function = function;
}

void KeypadEvents::onKeyUp(void (*function)(char)) {
    handlers[KEY_UP].function = function;
}

void KeypadEvents::onKeyPressed(void (*function)(char)) {
    handlers[KEY_PRESSED].function = function;
}

void KeypadEvents::readEvents() {
    rows[0] = analogRead(pinmap[0]);
    rows[1] = analogRead(pinmap[1]);
    rows[2] = analogRead(pinmap[2]);
    rows[3] = analogRead(pinmap[3]);


#ifdef DEBUG
    Serial.println("Readings: ");
#endif
    int last, next;
    for (int i = 0; i<4; i++) {
#ifdef DEBUG
        Serial.print(pinmap[i]);
        Serial.print(" = ");
        Serial.println(rows[i]);
#endif
        last = last_states[i];
        next = getCol(rows[i]);

        /* Possible outcomes:
         *  1) last == next --> no change
         *  2) last != next --> detect change
         *     buttons[i][last] = UP
         *     notifyUp(buttons[i][last])
         *     notifyPressed(buttons[i][last])
         *
         *     buttons[i][next] = DOWN
         *     notifyDown(buttons[i][next])
         */

        if (last != next) {
            /* CAVEAT: Ignoring the Pressed -> Pressed transition (for now)
             * e.g. last=2, next=3
             */
            if (next >= 0) {
                /* Button was pressed */
                handlers[KEY_DOWN].function(buttons[i][next]);
            } else {
                /* Button was released */
                handlers[KEY_UP].function(buttons[i][last]);
                handlers[KEY_PRESSED].function(buttons[i][last]);
            }
        }
        last_states[i] = next;
    }
}

int KeypadEvents::getCol(int reading) {
    if (GET_RANGE(col1, reading)) {
        return 0;
    }
    if (GET_RANGE(col2, reading)) {
        return 1;
    }
    if (GET_RANGE(col3, reading)) {
        return 2;
    }
    if (GET_RANGE(col4, reading)) {
        return 3;
    }
    return -1;
}
