#include <Automaton.h>
#include <Atm_led.h>
#include <Automaton_Adafruit_RGBLCDShield_Buttons.h>
#include "Atm_Menu.h"

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Atm_led led1, led2, led3, led4; 
Atm_Menu lcd_display;
Automaton_Adafruit_RGBLCDShield_Buttons lcd_buttons;
Factory factory; 

void setup() {
  
  // Initialize the machines
  led1.begin( 3 ).blink( 500 ).state( led1.START );
  led2.begin( 4 ).blink( 500 ).state( led2.START );
  led3.begin( 5 ).blink( 500 ).state( led3.START );
  led4.begin( 6 ).blink( 0 ).pause( 0 ).fade( 0 ).state( led4.START );
  lcd_display.begin( );
  lcd_buttons.begin( lcd_display ); // Link the buttons to the display

  // Add the initialized machines to the factory
  factory.add( led4 ).add( led3 ).add( led2 ).add( led1 );
  factory.add( lcd_display ).add( lcd_buttons );
}

void loop() {
  factory.cycle();
}

