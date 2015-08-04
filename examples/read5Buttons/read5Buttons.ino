/*
read5Buttons.ino
-This code demonstrates using this eRCaGuy_ButtonReader class to read 5 buttons at once.  This could be really useful, for example,
 to read a keypad that has buttons for up, down, left, right and enter.
eRCaGuy_ButtonReader example
By Gabriel Staples
http://electricrcaircraftguy.blogspot.com/
Written: 31 Oct. 2014

Library webpage: http://electricrcaircraftguy.blogspot.com/2014/05/ercaguybuttonreader-library-for-arduino.html
-I wanted a simple and universal, yet very powerful & reliable library to read a button or switch in such a way that I can
 easily implement toggled actions and momentary actions, know the true, debounced state of a button or switch at any given time, 
 and specify whether I want an action to take place when the button is *pressed* or *released.*  This library makes implementing all of
 these things easy for me, and I now use it on all of my projects that require reading a button or switch, so I wanted to share it with others.  
 Hopefully you find it useful too.
 
License for Library and Examples: GNU General Public License Version 3 (GPLv3) - https://www.gnu.org/licenses/gpl.html
-See library .h and .cpp files for details

Description:
-This example will continually check 5 buttons, and whenever one is pressed or released, it will output its status to the Serial Monitor
--Whenever a button is pressed it will also toggle LED 13 on or off

Circuit:
-Connect 5 buttons as follows, with one side of the button going to the following 5 pins, and the other side of each button to GND
Button    Arduino pin
left      10
right     11
up        12
down      A0
enter     A1
--the internal pull-up resistor is enabled on each pin to protect the pin from over-current

Instructions:
Upload the code, open the serial monitor, and play around pressing, releasing, and holding down the buttons, to see what happens!
*/

//include the library
#include <eRCaGuy_ButtonReader.h>

//Global Constants:
//5 button pins
const byte LEFT = 10; //the number of the pushbutton pin
const byte RIGHT = 11;
const byte UP = 12;
const byte DOWN = A0;
const byte ENTER = A1;

const byte ledPin = 13; // the number of the LED pin

//Define Button States:
const boolean BUTTON_PRESSED = LOW; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be LOW when the button is pressed; 
const boolean BUTTON_NOT_PRESSED = HIGH; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be HIGH when the button is NOT pressed

//instantiate objects of this library class
//if not explicitly stated, debounceDelay defaults to 50ms, and the _BUTTON_PRESSED value in the library defaults to LOW; see .h file for details

//eRCaGuy_ButtonReader left = eRCaGuy_ButtonReader(LEFT);
//eRCaGuy_ButtonReader right = eRCaGuy_ButtonReader(RIGHT);
//eRCaGuy_ButtonReader up = eRCaGuy_ButtonReader(UP);
//eRCaGuy_ButtonReader down = eRCaGuy_ButtonReader(DOWN);
//eRCaGuy_ButtonReader enter = eRCaGuy_ButtonReader(ENTER);

//Alternate instantiation technique:
eRCaGuy_ButtonReader left(LEFT);
eRCaGuy_ButtonReader right(RIGHT);
eRCaGuy_ButtonReader up(UP);
eRCaGuy_ButtonReader down(DOWN);
eRCaGuy_ButtonReader enter(ENTER);

//alternatively, the object instantiation could be explicit, as follows, for instance:
//eRCaGuy_ButtonReader left(LEFT,50,BUTTON_PRESSED); //note: the 50 here is the debounce delay in ms; increase if you get jitter on the button

void setup() 
{
  Serial.begin(115200);
  Serial.println(F("5 Button reader demo\n"
                   "By Gabriel Staples\n"));
  
  //configure pins
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  
  pinMode(ledPin, OUTPUT);

  // set initial LED state to OFF
  toggleLED();
  
  //Example of additional configuration settings that can be called for each button 
  //left.setDebounceDelay(50); //(optional); set debounceDelay to 50ms; uncomment this and increase the debounceDelay if the button_state jitters unexpectedly
  //left.setButtonPin(buttonPin); //(optional), since this was established during the object instantiation above
  //left.setPinStateWhenButtonPressed(HIGH); //uncomment this line if using a pull-down resistor on the button or switch instead of the internal pull-up resistor
}

void loop() 
{
  //local variables
  int8_t button_action; //see details below
  boolean button_state; //see details below
  
  //read button; use the ampersands (&) to pass the address to (pointers to) the variables as input parameters, so that the variables can be updated by the function
  //Details:
    //read the button action, and store it into the button_action variable; and read the button state, & store it into the button_state variable
    //The button state can be 0 or 1, for LOW or HIGH, respectively
    // button action indicates what just happened to the button: 
    //	0 = no-change in true, debounced button state since last time reading the button, or debounceDelay time not yet elapsed
    //	1 = button was just pressed by a human operator (debounceDelay had elapsed)
    // -1 = button was just released by a human operator (debounceDelay had elapsed)
  
  left.readButton(&button_action,&button_state);
  processButtonRead("left",button_action,button_state);
  
  right.readButton(&button_action,&button_state);
  processButtonRead("right",button_action,button_state);
  
  up.readButton(&button_action,&button_state);
  processButtonRead("up",button_action,button_state);
  
  down.readButton(&button_action,&button_state);
  processButtonRead("down",button_action,button_state);
  
  enter.readButton(&button_action,&button_state);
  processButtonRead("enter",button_action,button_state);

} //end of loop()

//Here you will do something useful, determined by the press or release of the button; I am simply toggling led 13 on and off in order 
//to demonstrate one use of a button as a toggle switch
void toggleLED()
{ 
  static boolean ledState = HIGH;
  ledState = !ledState; //invert led state
  digitalWrite(ledPin, ledState); //write to led
}

void processButtonRead(char* button_name,int8_t button_action,boolean button_state)
{
  //output data if a button press or release was detected, & toggle LED 13 on button *presses* only
  if (button_action != 0) //if an action has occured on the button
  {
    if (button_action==1)
    {
      Serial.println(button_name);
    }
    
    Serial.print("button_action = "); Serial.print(button_action); Serial.print(", "); 
    if (button_action==1)
    {
      Serial.print("Button PRESS detected");
    }
    else //button_action==-1
    {
      Serial.print("Button RELEASE detected");
    }
    
    Serial.print("; button_state = "); Serial.print(button_state); 
    Serial.print(", "); 
    if (button_state==BUTTON_PRESSED)
    {
      Serial.println("BUTTON_PRESSED");
    }
    else //button_state==BUTTON_NOT_PRESSED
    {
      Serial.println("BUTTON_NOT_PRESSED\n");
    }
    
    //toggle the led on every button press
    if (button_action==1) //if button just pressed
    {
      toggleLED(); //turn the LED on if off, and off if on
    }
    //alternately, you could comment out the above if statement, and use this one below instead, if you desire to do an action on the *release* of the button
    //instead of on the *press* of the button
//    if (button_action==-1) //if button just released 
//    {
//      toggleLED(); //turn the LED on if off, and off if on
//    }
  }
}


