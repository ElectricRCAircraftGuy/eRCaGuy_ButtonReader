/*
readButton.ino
-This code differs from readButtonVerbose.ino ONLY in that it does not output the button status every 0.5 seconds; rather, it only outputs the button status when a 
 button *press* or *release* is detected.
eRCaGuy_ButtonReader example
By Gabriel Staples
http://electricrcaircraftguy.blogspot.com/
31 May 2014

Library webpage: http://electricrcaircraftguy.blogspot.com/2014/05/ercaguybuttonreader-library-for-arduino.html
-I wanted a simple and universal, yet very powerful & reliable library to read a button or switch in such a way that I can
 easily implement toggled actions and momentary actions, know the true, debounced state of a button or switch at any given time, 
 and specify whether I want an action to take place when the button is *pressed* or *released.*  This library makes implementing all of
 these things easy for me, and I now use it on all of my projects that require reading a button or switch, so I wanted to share it with others.  
 Hopefully you find it useful too.
 
License for Library and Examples: GNU Lesser General Public License Version 3 (LGPLv3) - https://www.gnu.org/licenses/lgpl.html
-See library .h and .cpp files for details

Description:
-This example will continually check the button, and whenever it is pressed or released, it will output its status to the Serial Monitor
--Whenever the button is pressed it will toggle LED 13 on or off

Circuit:
-Connect a button from digital pin 5 to GND
--the internal pull-up resistor is enabled on pin 5 to protect the pin from over-current

Instructions:
Upload the code, open the serial monitor, and play around pressing, releasing, and holding down the button, to see what happens!
*/

//include the library
#include <eRCaGuy_ButtonReader.h>

//Global Constants:
//Pins:
const byte buttonPin = 5; //the number of the pushbutton pin
const byte ledPin = 13; // the number of the LED pin
//Define Button States:
const boolean BUTTON_PRESSED = LOW; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be LOW when the button is pressed; 
const boolean BUTTON_NOT_PRESSED = HIGH; //if using a pull-up resistor (ex: INPUT_PULLUP) on your button, the buttonPin will be HIGH when the button is NOT pressed

//instantiate an object of this library class; call it "button1"
//if not explicitly stated, debounceDelay defaults to 50ms, and the _BUTTON_PRESSED value in the library defaults to LOW; see .h file for details
eRCaGuy_ButtonReader button1 = eRCaGuy_ButtonReader(buttonPin); 
//alternatively, the object instantiation could be explicit, as follows:
//eRCaGuy_ButtonReader button1 = eRCaGuy_ButtonReader(buttonPin,50,BUTTON_PRESSED);

void setup() 
{
  Serial.begin(115200);
  
  //configure pins
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // set initial LED state to OFF
  toggleLED();
  
  //configure button1
  //button1.setDebounceDelay(50); //(optional); set debounceDelay to 50ms; uncomment this and increase the debounceDelay if the button_state jitters unexpectedly
  //button1.setButtonPin(buttonPin); //(optional), since this was established during the object instantiation above
  //button1.setPinStateWhenButtonPressed(HIGH); //uncomment this line if using a pull-down resistor on the button or switch instead of the internal pull-up resistor
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
  button1.readButton(&button_action,&button_state);
  
  //output data if a button press or release was detected, & toggle LED 13 on button *presses* only
  if (button_action != 0) //if an action has occured on the button
  {
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
      Serial.println("BUTTON_NOT_PRESSED");
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

  //THE BELOW SEGMENT OF CODE IS COMMENTED OUT FOR readButton.ino, but NOT for readButtonVerbose.ino
//  else //button_action==0
//  {
//    //if there is no new action on the button, let's print out the button_state every 0.5 seconds, to see whether the button is currently NOT being pressed, 
//    //or whether it is being held down continuously
//    static unsigned long t_start = millis(); //ms; a time stamp to ensure printouts only happen every 0.5 seconds
//    if (millis() - t_start >= 500) //if 500ms (0.5 sec) has elapsed
//    {
//      t_start = millis(); //ms; update
//      if (button_state==BUTTON_PRESSED)
//      {
//        Serial.println("button is being held down");
//      }
//      else //button_state==BUTTON_NOT_PRESSED
//      {
//        Serial.println("button is just sitting there, NOT pressed");
//      }
//    }
//  }
} //end of loop()

//Here you will do something useful, determined by the press or release of the button; I am simply toggling led 13 on and off in order 
//to demonstrate one use of a button as a toggle switch
void toggleLED()
{ 
  static boolean ledState = HIGH;
  ledState = !ledState; //invert led state
  digitalWrite(ledPin, ledState); //write to led
}
