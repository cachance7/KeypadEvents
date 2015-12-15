#ifndef KEYPAD_EVENTS_H
#define KEYPAD_EVENTS_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

/* Event Codes */
#define KEY_DOWN 0
#define KEY_UP 1
#define KEY_PRESSED 2

/* Total number of event codes */
#define EVENT_COUNT 3

/* Key States */
#define UP 0
#define DOWN 1

//#ifndef ROW1PIN
//#define ROW1PIN 1
//#endif
//
//#ifndef ROW2PIN
//#define ROW2PIN 2
//#endif
//
//#ifndef ROW3PIN
//#define ROW3PIN 3
//#endif
//
//#ifndef ROW4PIN
//#define ROW4PIN 4
//#endif

#ifndef R1
#define R1 10000
#endif

#ifndef R2
#define R2 22000
#endif

#ifndef R3
#define R3 47000
#endif

#ifndef R4
#define R4 68000
#endif

#ifndef RCOMM
#define RCOMM 100000
#endif

#ifndef VCC
#define VCC 5.0
#endif

/* For the default resistor values, this is a pretty good default. */
#ifndef TOLERANCE
#define TOLERANCE 0.004
#endif

#define ANALOG_COUNTS(r) ((VCC / 5.0) * 1024 * RCOMM / (RCOMM + r))
#define PRINT_RANGE(col)({Serial.print(col - (col * TOLERANCE)); Serial.print(" < " #col " < "); Serial.print(col + (col * TOLERANCE)); Serial.println();})
#define GET_RANGE(col,reading) ((col - (col * TOLERANCE)) < reading && reading < (col + (col * TOLERANCE)))

class KeypadEvents {
    public:
        KeypadEvents(int[]);
        void onKeyDown(void(*)(char));
        void onKeyUp(void(*)(char));
        void onKeyPressed(void(*)(char));  // Down and up
        void init();
        void readEvents();

    private:
        int pinmap[4];
        int getCol(int);
        typedef struct _callback {
			void (*function)(char);
		} KeyEventCallback;
        KeyEventCallback handlers[EVENT_COUNT];
        const float col1;
        const float col2;
        const float col3;
        const float col4;
        int rows[4];
        int col;

        static char buttons[4][4];
        int last_states[4]; // this is the last known count of each row
};

#endif
