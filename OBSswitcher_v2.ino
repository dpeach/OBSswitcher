/*
 * OBS Studio Control box
 * A poor man's Tricaster
 * 15 April 2020 -- dpeach
 *
 * A device to control video streaming and camera switching using
 * eight buttons. These are configurable, but in the original device
 * and default state of this code, here is how it was intended.
 *      *                               *
 *   Start/Stop                   Mute/Unmute
 *  CNTL+SHIFT+1                  CNTL+SHIFT+0
 *
 *      *               *               *
 *   Scene 1         Scene 2         Scene 3
 * CNTL+SHIFT+F1  CNTL+SHIFT+F2  CNTL+SHIFT+F3
 *
 *      *               *               *
 *   Scene 4         Scene 5           ALT
 * CNTL+SHIFT+F4  CNTL+SHIFT+F5   ALT+Other Button Content
 */
 
 
#include <Keyboard.h>
// 5 buttons for 5 scenes. The plan is to have an ALT button to pair
// with these to give 5 more.
const int scene1 = 9;
const int scene2 = 8;
const int scene3 = 7;
const int scene4 = 6;
const int scene5 = 5;
const int start = 4;
const int mute = 3;
const int alt = 2;

void setup() {
  pinMode(scene1,INPUT_PULLUP);  // sets pins to input & pulls them high w/ internal resistor
  pinMode(scene2,INPUT_PULLUP);
  pinMode(scene3,INPUT_PULLUP);
  pinMode(scene4,INPUT_PULLUP);
  pinMode(scene5,INPUT_PULLUP);
  pinMode(start,INPUT_PULLUP);
  pinMode(mute,INPUT_PULLUP);
  pinMode(alt,INPUT_PULLUP);
  
  Serial.begin(9600);       // Begin serial comms for debugging. [Because the 
  Keyboard.begin();         // Arduino Leonardo acts as a keyboard, it can't be
                            // a keyboard and talk with serial at the same time.]
}

void loop() {
 char key = 0x00;
 bool altPressed = (digitalRead(alt) == 0);

 if (digitalRead(scene1) == 0)  // if scene1 button is pushed
  {
    key = KEY_F1;
  }
  else if (digitalRead(scene2) == 0)  // if scene2 button is pressed
  { 
    key = KEY_F2;
  }
  else if (digitalRead(scene3) == 0){  //if scene3 button is pressed
    key = KEY_F3;
  }
  else if (digitalRead(scene4) == 0)  // if scene4 button is pressed
  { 
    key = KEY_F4;
  }
  else if (digitalRead(scene5) == 0){  //if scene5 button is pressed
    key = KEY_F5;
  }
  else if (digitalRead(start) == 0)  // if record/stream button is pressed
  { 
    key = '1';
  }
  else if (digitalRead(mute) == 0){  //if mute button is pressed
    key = '0';
  }

  if (key != 0x00)
  {
    if (altPressed)
    {
      Keyboard.press(KEY_LEFT_ALT);
    }
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(key);  // Three previous lines sent together.
    delay(500);           // delay of 1/2 second to only get one press
    Keyboard.releaseAll();
  }
  Keyboard.end();
}
