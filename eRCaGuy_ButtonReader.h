/*
eRCaGuy_ButtonReader
Library webpage: http://www.electricrcaircraftguy.com/2014/05/ercaguybuttonreader-library-for-arduino.html
-I wanted a simple and universal, yet very powerful & reliable library to read a button or switch in such a way that I can
 easily implement toggled actions and momentary actions, know the true, debounced state of a button or switch at any given time, 
 and specify whether I want an action to take place when the button is *pressed* or *released.*  This library makes implementing all of
 these things easy for me, and I now use it on all of my projects that require reading a button or switch, so I wanted to share it with others.  Hopefully you find it useful too.
 
 By Gabriel Staples
 http://www.ElectricRCAircraftGuy.com
 -My contact info is available by clicking the "Contact Me" tab at the top of my blog.
 Written: 30 May 2014
 Last Updated: 31 Oct 2014
 
 Version (newest on top): 
 1.1 - fixed bug which prevented multiple buttons from working
 1.0 - first release
 
 History (newest on top):
 20141031 - V1.1 release; fixed major bug which prevented multiple buttons from working
 20140531 - V1.0 release; first version created
 
 Credits:
 1) This file was created and edited in Notepad++ (http://notepad-plus-plus.org/)
 2) The core of my debouncing algorithm is based on the Arduino "Debounce" example (which is a very thorough and well-written debounce
	by the way)	here:  http://arduino.cc/en/Tutorial/Debounce
	-The history of the above example, in order to properly thank and give credit to these people, is:
		-created 21 November 2006 by David A. Mellis
		-modified 30 Aug 2011 by Limor Fried (LadyAda)
		-modified 28 Dec 2012 by Mike Walters
*/

/*
===================================================================================================
  LICENSE & DISCLAIMER
  Copyright (C) 2014 Gabriel Staples.  All right reserved.
  
  This file is part of eRCaGuy_ButtonReader.
  
  I AM WILLING TO DUAL-LICENSE THIS SOFTWARE. HOWEVER, UNLESS YOU HAVE PAID FOR AND RECEIVED A RECEIPT
  FOR AN ALTERNATE LICENSE AGREEMENT, FROM ME, THE COPYRIGHT OWNER, THIS SOFTWARE IS LICENSED AS FOLLOWS: 
  
  ------------------------------------------------------------------------------------------------
  License: GNU General Public License Version 3 (GPLv3) - https://www.gnu.org/licenses/gpl.html
  ------------------------------------------------------------------------------------------------
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/
===================================================================================================
*/

#ifndef eRCaGuy_ButtonReader_h
#define eRCaGuy_ButtonReader_h

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class eRCaGuy_ButtonReader
{
  public:
    //declare class constructor method
    eRCaGuy_ButtonReader(uint8_t buttonPin,unsigned int debounceDelay = 50,boolean pinStateWhenButtonPressed = LOW); //default debounceDelay, if not specified, is 50ms; the default state of the pin when the button is pressed is LOW (this is valid when using a pull-up resistor on the pin)
	
		//declare other public class methods (functions)
		
		//function to set the debounceDelay time (in ms)
		void setDebounceDelay(unsigned int debounceDelay = 50); //default is 50ms
		
		//function to set or change the pin the button is connected to
		void setButtonPin(uint8_t buttonPin); 
		
		//function to specify whether the button is considered pressed when the buttonPin is HIGH or LOW
		void setPinStateWhenButtonPressed(boolean pinStateWhenButtonPressed = LOW); //the default is that the button is considered pressed when the buttonPin is LOW (this is valid when using a pull-up resistor on the pin)
		
		//function to find out what the current debounceDelay is set to
		unsigned int getDebounceDelay();
		
		//read the button action, and store it into the button_action variable; and read the button state, & store it into the button_state variable
		//The button state can be 0 or 1, for LOW or HIGH, respectively
		// button action indicates what just happened to the button: 
		//	0 = no-change in true, debounced button state since last time reading the button, or debounceDelay time not yet elapsed <--*perhaps* in the future, output a 3 to indicate debounceDelay time not yet elapsed
		//	1 = button was just pressed by a human operator (debounceDelay had elapsed)
			// -1 = button was just released by a human operator (debounceDelay had elapsed)
		void readButton(int8_t* button_action, boolean* button_state);
		
		//Public class constants (defined in .cpp file)
		static const int8_t PRESSED_ACTION, RELEASED_ACTION;
		
									   
  private:
		//declare private class methods (functions)
		//N/A
	  //variables accessible by this class only
		uint8_t _buttonPin;
		unsigned int _debounceDelay;
		boolean _BUTTON_PRESSED;
		boolean _BUTTON_NOT_PRESSED;
		//for readButton method
		unsigned long _lastBounceTime;
		unsigned int _reading_old;
		boolean _buttonState;
		boolean _buttonState_old;
};

#endif
