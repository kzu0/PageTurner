/*
  PageTurner

  Uses a pedal switch to send a mouse or a keyboard command to turn pages on desktop or mobile devices

  #define KEY_UP_ARROW      0xDA
  #define KEY_DOWN_ARROW    0xD9
  #define KEY_LEFT_ARROW    0xD8
  #define KEY_RIGHT_ARROW   0xD7
  #define KEY_PAGE_UP       0xD3
  #define KEY_PAGE_DOWN     0xD6

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardAndMouseControl
  https://docs.arduino.cc/built-in-examples/digital/Debounce/
*/

#include "Keyboard.h"
#include "Mouse.h"

const int pedal = 2;

int state = LOW;
int lastState = LOW;
int currentState = LOW;

unsigned long toggleTime = 0;     // the last time the output pin was toggled
unsigned long debounceDelay = 25; // ms

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(pedal, INPUT);

  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  
  // for debug
  //Serial.begin(9600);
}

void loop() {

  currentState = digitalRead(pedal);

  // If the switch changed, due to noise or pressing:
  if (currentState != lastState) {
    toggleTime = millis(); // reset the debouncing timer
  }
  
  // Whatever the reading is at, if it's been there for longer 
  // than the delay, take it as the actual current state:
  if ((millis() - toggleTime) > debounceDelay) {

    if (state != lastState) {
      state = currentState;
      
      if (state == HIGH) {
        //Serial.println("CLICKED");
        //Mouse.click(MOUSE_LEFT);
      } else {
        //Serial.println("RELEASED");
        //Mouse.click(MOUSE_RIGHT);
        Keyboard.write(KEY_RIGHT_ARROW);
      }

      digitalWrite(LED_BUILTIN, state);
    }
  }
  lastState = currentState;
}


